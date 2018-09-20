#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <fstream>
#include <memory>
#include <functional>
#include <sstream>
#include <string>

#include "kdtree.h"

using namespace std;

typedef unsigned int uint;

int dim ;
kdtree* kdTree = new kdtree();

struct point{
	double* data ;	
	double operator[](int idx) const { return data[idx]; }
};

vector<point> mydata;
vector<int> label;

bool getNeighbours(int index, float radius, int minpts, vector<int>& neighbours) 
{
	std::unique_ptr<double[]> pos(new double[dim]);
    for (int c = 0; c < dim; ++c) 
    {
        pos[c] = (double)(mydata)[index][c];        
    }

	kdres* res = kd_nearest_range(kdTree, pos.get(), radius);
	int number_near = kd_res_size(res);

	if (number_near > minpts)
	{
		while (!kd_res_end(res))
		{
			point* next = (point*)kd_res_item(res, pos.get());
			uint newpid = (uint)(next - &(mydata)[0]);
	        if(index != newpid) 
	        	neighbours.push_back(newpid);			
			kd_res_next(res);
		}
	}
	return number_near > minpts;
}

void cluster(vector<int>& points, int ncluster, float radius, int minpts)
{
	vector<int> neighbours;

	for(int i=0; i<points.size(); i++)
	{
		if(label[points[i]] ==0)
		{			
			label[points[i]] = ncluster;
			neighbours.push_back(points[i]);
		}
	}

	for (int i = 0; i < (int)neighbours.size(); i++)
	{
		int index = neighbours[i];
		
		vector<int> neighbours2;	

		if(getNeighbours(index, radius, minpts, neighbours2))
		{			
			for (int j = 0; j < (int)neighbours2.size(); j++)
			{
				int in = neighbours2[j];
		
				if (label[in] <= 0)
				{
					label[in] = ncluster;
					neighbours.push_back(in);
				}
			}
		}
	}
}

int dbscan( float radius, int minpts)
{
	int ncluster = 1;
	int index = 0;
	for (index =0; index< mydata.size(); index++)
	{				
		if (label[index]==0)
		{
			label[index] = -1;			
			vector<int> neighbourhood;
			
			if(getNeighbours(index, radius, minpts, neighbourhood))
			{
				label[index] = ncluster;				

				cluster(neighbourhood, ncluster, radius, minpts);
				ncluster++;
			}
		}		
	}
	return ncluster;
}

// kdtree* buildKdtree(vector<vector<double>> &mydata)
// {
//     kdtree* kdtree = kd_create(dim);
//     std::unique_ptr<double[]> v(new double[dim]);
//     for (int r = 0; r < mydata.size(); ++r) 
//     {        
//         for (int c = 0; c < dim; ++c) 
//         {
//             v[c] = (double)(mydata)[r][c];
//         }
//         kd_insert(kdtree, v.get(), (void*)&(mydata)[r]);
//     }
// 	return kdtree;	    
// }

kdtree* buildKdtree()
{
    kdtree* kdtree = kd_create(dim);
    std::unique_ptr<double[]> v(new double[dim]);
    for (int r = 0; r < mydata.size(); ++r) 
    {        
        for (int c = 0; c < dim; ++c) 
        {
            v[c] = (double)(mydata)[r][c];
        }
        kd_insert(kdtree, v.get(), (void*)&(mydata)[r]);        
    }
	return kdtree;	    
}

int main(int argc, char * argv [])
{
	std::ifstream infile(argv[3]);
	std::string line;
	
	if (std::getline(infile, line))	
	{
		std::istringstream iss(line);
		vector<double> row;
		double a;
		while (iss >> a)
	    { 
	    	row.push_back(a);	    	
	    }
	    dim = row.size();
	    point p;
	    p.data = new double[dim];
	    for(int i=0; i<dim; i++)
	    {
	    	p.data[i] = row[i];
	    }
	    mydata.push_back(p);
	}

	while (std::getline(infile, line))
	{		
	    std::istringstream iss(line);
	    double a;
	    point p;
	    p.data = new double[dim];
	    int i = 0;
	    while (iss >> a)
	    { 
	    	p.data[i] = a;
	    	i++;
	    }	    	  	   
	    mydata.push_back(p);
	}
		
	label.resize(mydata.size());
	kdTree = buildKdtree();
	float radius = stof(argv[1]);
	int minpts = stoi(argv[2])-1;
	int h = dbscan(radius, minpts);

	vector<vector<int>> clusters = vector<vector<int>> (h);
	for (int j=0; j<label.size();j++)
	{
		if(label[j]!=-1)
			clusters[label[j]].push_back(j);
		else
			clusters[0].push_back(j);
	}

	for(int j =1; j<h; j++)
	{
		printf("#%d\n",j-1);
		for(int k = 0; k<clusters[j].size(); k++)
		{
			printf("%d\n", clusters[j][k]);
		}
	}
	if(clusters[0].size()!=0)
		printf("#outliers\n");
	for(int j =0;j<clusters[0].size(); j++)
	{	
		printf("%d\n", clusters[0][j]);
	}
}