#include<bits/stdc++.h>

#include <string>     // std::string, std::stof
using namespace std;
#define FE(i,L,R) for (int i = L; i <= R; i++)
#define printA(a,L,R) FE(il,L,R) cout << a[il] << (il==R?'\n':' ')
#define printV(a) printA(a,0,a.size()-1)
#define printVV(a) FE(ik,0,a.size()-1) printV(a[ik])


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

float norm(vector<float> x,vector<float> y)
{
	float ans=0;
	for(int i=0;i<min(x.size(),y.size());i++)
	{
		ans+=(x[i]-y[i])*(x[i]-y[i]);
	}
	return (ans);
}

vector<float> adder(vector<float> x,vector<float> y)
{
	std::vector<float> ans(min(x.size(),y.size()));
	for(int i=0;i<ans.size();i++)
	{
		ans[i]=x[i]+y[i];
	}
	return ans;
}
vector<float> divider(vector<float> x,int b)
{
	std::vector<float> ans(x.size());
	for(int i=0;i<ans.size();i++)
	{
		// cout<<x[i]<<" "<<b<<" "<<ans.size()<<endl;
		ans[i]=x[i]/b;
		// cout<<ans[i]<<" w "<<b<<" "<<ans.size()<<endl;
	}
	return ans;
}


int main(int argc,char** argv)
{
	std::vector<vector<float> > database;
    std::vector<std::vector<float> > v;
    string record;
    ifstream in(argv[2]);
    while ( std::getline( in, record ) )
    {
        std::istringstream is( record );
        std::vector<float> row( ( std::istream_iterator<float>( is ) ),
                                 std::istream_iterator<float>() );
        database.push_back( row );
    }

	int dimension=database[0].size();
	int k = atoi(argv[1]);


	// cout<<k<<" "<<dimension<<endl;
	std::vector<std::vector<float> > centroids(k,std::vector<float>(dimension));
	std::vector<int> randoms(k);
	vector<int> centroid_num(database.size());
	for(int i=0;i<k;i++)
	{
		randoms[i]=rand()%(database.size());
		// cout<<i<<endl;
		while(invec(randoms,randoms[i],i))
		{
			// cout<<i<<endl;
			randoms[i]=rand()%(database.size());
		}
		// centroids[i]=database[i];
	}
	for(int i=0;i<k;i++)
	{
		centroids[i]=database[randoms[i]];
	}

	std::vector<int> num_points(k);
	for(int i=0;i<database.size();i++)
	{
		float a1=INT_MAX;
		for(int j=0;j<k;j++)
		{
			if(norm(database[i],centroids[j])<a1)
			{
				a1=norm(database[i],centroids[j]);
				centroid_num[i]=j;
			}
		}
		num_points[centroid_num[i]]++;
	}
	// printVV(centroids);
int num_itera=0;
while(num_itera<5000)
	{
		int change=0;
		for(int i=0;i<database.size();i++)
		{
			float a1=norm(database[i],centroids[centroid_num[i]]);
			for(int j=0;j<k;j++)
			{
				if(norm(database[i],centroids[j])<a1)
				{
					change=1;
					a1=norm(database[i],centroids[j]);
					num_points[centroid_num[i]]--;
					centroid_num[i]=j;
					num_points[centroid_num[i]]++;
				}
			}
		}
		std::vector<std::vector<float> > centroids_temp(k,std::vector<float>(dimension));

		for(int i=0;i<database.size();i++)
		{
			
			centroids_temp[centroid_num[i]]=adder(centroids_temp[centroid_num[i]],database[i]);
		}
		cout<<"centroids_temp"<<endl;	
		printVV(centroids_temp);
		cout<<"num_points"<<endl;	
		printV(num_points);

		for(int i=0;i<k;i++)
		{
			centroids_temp[i]=divider(centroids_temp[i],num_points[i]);
		}
		// cout<<"centroids_temp"<<endl;	
		// printVV(centroids_temp);

		if(!change)
		{
			for(int i=0;i<k;i++)
			{
				if(centroids_temp[i]!=centroids[i])
				{
					change=1;
					break;
				}
			}			
		}
		if(!change)
		{
			break;
		}
		for(int i=0;i<k;i++)
		{
			centroids[i]=centroids_temp[i];
		}
	// cout<<"centroid_num"<<endl;	
	// printV(centroid_num);

	// cout<<"centroids"<<endl;	
	// printVV(centroids);

	// cout<<"num_itera"<<num_itera<<endl<<endl;	


	num_itera++;
	}
	// cout<<"centroids"<<endl;	
	// printVV(centroids);

	// cout<<"num_points"<<endl;
	// printV(num_points);
	vector<vector<int> > indexe(k);
    ofstream myfile;
    myfile.open ("kmeans.txt");
    for(int i=0;i<database.size();i++)
    {
    	indexe[centroid_num[i]].push_back(i);
    }
    for(int i=0;i<k;i++)
    {
    	myfile<<"#"<<i<<"\n";
    	for(int j=0;j<indexe[i].size();j++)
    	{
    		myfile<<indexe[i][j]<<"\n";
    	}
    }
    myfile.close();
	return 0;
}