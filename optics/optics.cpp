#include<bits/stdc++.h>
#include "nanoflann.hpp"
using namespace nanoflann;
#include "KDTreeVectorOfVectorsAdaptor.h"
#include <string>   

using namespace std;
#define FE(i,L,R) for (int i = L; i <= R; i++)
#define printA(a,L,R) FE(il,L,R) cout << a[il] << (il==R?'\n':' ')
#define printV(a) printA(a,0,a.size()-1)
#define printVV(a) FE(ik,0,a.size()-1) printV(a[ik])
#define sq(a) a*a
#define printp(a,L,R) FE(il,L,R) cout << a[il].first<<" "<<a[il].second << (il==R?'\n':' ')
#define printVp(a) printp(a,0,a.size()-1)

std::vector<vector<double> > database;
double epsilon = 10;
int min_points = 8;
std::vector<double> reachability_dist;
std::vector<int> is_processed;
std::vector<int> ordered_list_ans;

int invec(std::vector<int> a,int b,int c)
{
	for(int i=0;i<=c-1;i++)
	{
		if(b==a[i])
		{
			return 1;
		}
	}
	return 0;
}

double norm(vector<double> x,vector<double> y)
{
	double ans=0;
	for(int i=0;i<min(x.size(),y.size());i++)
	{
		ans+=(x[i]-y[i])*(x[i]-y[i]);
	}
	return (ans);
}
double norm_index(int x,int y)
{
	return norm(database[x],database[y]);
}

vector<double> adder(vector<double> x,vector<double> y)
{
	std::vector<double> ans(min(x.size(),y.size()));
	for(int i=0;i<ans.size();i++)
	{
		ans[i]=x[i]+y[i];
	}
	return ans;
}
vector<double> divider(vector<double> x,int b)
{
	std::vector<double> ans(x.size());
	for(int i=0;i<ans.size();i++)
	{
		ans[i]=x[i]/b;
	}
	return ans;
}

void Update(int index,std::vector< pair<long unsigned int,double> >& neighbors_radius, set< pair<double, int> >&seeds)
{
	double core_dist = neighbors_radius[min_points-1].second;
	for(int i=0;i<neighbors_radius.size();i++)
	{
		pair<int, double> object = neighbors_radius[i];
		int n_index=object.first;
		if(is_processed[object.first]==0)
		{
			double new_r_dist=max(object.second,core_dist);
			// cout<<"why do we fall"<<reachability_dist[n_index]<<" + "<<new_r_dist<<endl;
			if(new_r_dist>sq(epsilon))
			{
				continue;
			}
			else
			{
				// cout<<"why do we fall"<<reachability_dist[n_index]<<" ";
				if(reachability_dist[n_index]<0)
				{
					// cout<<"why do we fall"<<reachability_dist[n_index]<<" ";
					seeds.insert({new_r_dist,n_index});
					reachability_dist[n_index]=new_r_dist;
					
					
				}
				else
				{
					if (new_r_dist < reachability_dist[n_index])
					{
						set< pair<double, int> >::iterator it1 ;
						double old_r_dist=	reachability_dist[n_index];
						reachability_dist[n_index] = new_r_dist;
						it1= seeds.find({(old_r_dist), n_index});
						
						
						if (it1 != seeds.end() ) 
						{
							seeds.erase(it1);
							seeds.insert({new_r_dist, n_index});
						}
					}					
				}
			}
		}
	}
}


int main(int argc,char** argv)
{
    string record;
    ifstream in(argv[3]);
    epsilon=stod(argv[1]);
    // epsilon=sq(epsilon);
    min_points=stoi(argv[2]);
    while ( std::getline( in, record ) )
    {
        std::istringstream is( record );
        std::vector<double> row( ( std::istream_iterator<double>( is ) ),
                                 std::istream_iterator<double>() );
        database.push_back( row );
    }
    // printVV(database);
	int dimension=database[0].size();
	reachability_dist.resize(database.size());
	for(int i=0;i<database.size();i++)
	{
		reachability_dist[i]=-1;
	}
	is_processed.resize(database.size());
	std::vector<int> ordered_list_ans;
	ordered_list_ans.reserve(database.size());
    
	KDTreeVectorOfVectorsAdaptor< vector< vector<double> >, double > mat_index(dimension, database, 10);
	mat_index.index->buildIndex();
	// printVV(database);

	FE(index,0,database.size()-1)
	{
		if(is_processed[index]==1)
		{
			continue;
		}
		else
		{
			cout<<index<<" ";
			is_processed[index]=1;
			reachability_dist[index]=-1;
			ordered_list_ans.push_back(index);
			std::vector<double> reference_vector = database[index];
			std::vector<int> indices_list(min_points);
			indices_list.reserve(min_points);
			std::vector<double> distance_list(min_points);
			distance_list.reserve(min_points);

			// // nanoflann::KNNResultSet<double> resultSet(min_points);
			// // resultSet.init(&indices_list[0], &distance_list[0]);
			// // mat_index.index->findNeighbors(resultSet, &reference_vector[0], nanoflann::SearchParams(10));

			// 		vector<double> pointQueryQ(dimension);
			// 		for (size_t i = 0; i < dimension; ++i)
			// 			pointQueryQ[i] = database[index][i];

			vector<pair<long unsigned int,double> > neighbors_radius;
			nanoflann::SearchParams params ;//= nanoflann::SearchParams(10) ;
			params.sorted=1;
			int num_points = mat_index.index->radiusSearch(&reference_vector[0], sq(epsilon), neighbors_radius, params);
			// cout<<"neighbours "<<index<<endl;
			// printVp(neighbors_radius);
			// cout<<"neighbours"<<endl;

			// cout<<neighbors_radius.size()<<" ";
			if((neighbors_radius.size())>=min_points)
			{
				// cout<<neighbors_radius.size()<<" neigh"<<endl;
				set< pair<double, int> > seeds;
				double core_dist_index = neighbors_radius[min_points-1].second;
				Update(index,neighbors_radius,seeds);
					// int x=0;
					// for (std::set<pair<double, int> >::iterator it=seeds.begin(); it!=seeds.end(); ++it)
    	// 			{		std::cout <<' ' << it->first<<' '<<it->second<<endl;}
				while(seeds.size()!=0)
				{

					// cout<<seeds.begin()->first<<" "<<seeds.begin()->second<<" "<<index<<endl;
					int index_n=seeds.begin()->second;
					seeds.erase(seeds.begin());
					if(is_processed[index_n])
					{
						cout<<"wtf";
					}
					cout<<index_n<<" ";
					is_processed[index_n]=1;
					ordered_list_ans.push_back(index_n);
					std::vector<double> new_vec = database[index_n];

					vector<pair<long unsigned int,double> > ret_matches2;
					nanoflann::SearchParams params2;
					params2.sorted=1;
					const size_t nMatches2 = mat_index.index->radiusSearch(&new_vec[0], sq(epsilon), ret_matches2, params2);
					if(ret_matches2.size()>=min_points)
					{
						Update(index_n,ret_matches2,seeds);
					}

				}
			}
		}
	}

    ofstream myfile;
    myfile.open ("optics.txt");
	// myfile<<"#"<<"\n";
	// printV(ordered_list_ans);
	FE(i,0,ordered_list_ans.size()-1)
	{
		if(reachability_dist[ordered_list_ans[i]]==-1)
		{
		myfile<<epsilon*2<<"\n";		
		}
		else
		{
			myfile<<sqrt(reachability_dist[ordered_list_ans[i]])<<"\n";	
		}
		
	}
    myfile.close();

	return 0;
}