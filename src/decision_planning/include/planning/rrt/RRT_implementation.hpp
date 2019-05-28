#include <iostream>
#include "./RRT.hpp"
#include "./utils.hpp"
#include "environment/environment.h"

namespace rrt
{
	template <class T>
	void RRT<T>::setEndPoints(Utils::Point<T> start, Utils::Point<T> end)
	{
		startPoint=start;
		endPoint=end;
	}

	template <class T>
	void RRT<T>::setHalfDimensions(double a, double b)
	{
		halfDimensionX=a;
		halfDimensionY=b;
	}

	template <class T>
	void RRT<T>::setOrigin(Utils::Point<T> pt)
	{
		origin=pt;
	}

	template <class T>
	std::deque<Utils::Point<T> > RRT<T>::getPointsOnPath()
	{
		return pathPoints;
	}

	template <class T>
	void RRT<T>::setStepLength(double value)
	{
		stepLength=value;
	}

	template <class T>
	void RRT<T>::setMaxIterations(int value)
	{
		maxIterations=value;
	}

	template <class T>
    bool RRT<T>:: plan(vector<obstacle> obs_info, int direction)
	{
		int count=0;
		int check=0;
		tree.push_back(std::pair< Utils::Point<T>, Utils::Point<T> > (startPoint,startPoint));
                int count1=0;
		while( check < maxIterations)
		{
			//std::cout<<"In Planning Loop"<<std::endl;
			Utils::Point<T> next;
			int arr[]={1};
			std::pair  <Utils::Point <T>,Utils::Point <T> >  mid = treeComplete(arr);
			if(mid.first!=mid.second)
			{
				std::cout<<"Tree complete!!"<<std::endl;
				int start_time=clock();
                                growTree(endPoint,direction);
				int end_time=clock();
				std::cout<<"Time to generate path = "<<end_time-start_time<<std::endl;
				generatePath(startPoint,endPoint);
				return true;
			}
			else if(count%biasParameter==0)
			{
				//std::cout<<"Adding Next Biased Point to tree!!"<<std::endl;
				count=0;
                                count1=0;
				do{
                                  count1=count1+1;
                                  next= generateBiasedPoint(1,direction);
                                }while(checkPoint(next,obs_info)!=true && count1<20);
				//std::cout<<" : "<<next.x<<","<<next.y<<std::endl;
			}
			else
			{
				//std::cout<<"Adding next point to tree!!"<<std::endl;
                                count1=0;
                                do{
                                  count1=count1+1;
                                  next = generatePoint(direction);
                                }while(checkPoint(next,obs_info)!=true && count1<20);
				//std::cout<<" : "<<next.x<<","<<next.y<<std::endl;
			}
			//std::cout<<" Growing Tree next : "<<next.x<<","<<next.y<<std::endl;
                        if(count1==20){
                          std::cout<<"Path Not Found"<<std::endl;
                          return false;
                        }
                        growTree(next,direction);
			count++;
			check++;
			//std::cout<<"check= "<<check<<", count= "<<count<<std::endl;
		}
		std::cout<<"Path Not Found"<<std::endl;
		return false;
	}

	template <class T>
    void RRT<T>::growTree(Utils::Point<T> next,int direction)
	{
		//growing the tree by adding node
		//std::cout<<"finding parent in tree of size = "<<tree.size()<<std::endl;
		Utils::Point<T> parent;
        parent= findClosestNode(next,direction).first;
		//std::cout<<"current : "<<next.x<<","<<next.y<<"| parent : "<<parent.x<<","<<parent.y<<std::endl;
		tree.push_back( std::pair< Utils::Point<T>, Utils::Point<T> > (next,parent));
		//std::cout<<"Tree grown"<<std::endl;
		//add pruning code to keep size of tree under control
	}

//	template <class T>
//	void RRT<T>::setCheckPointFunction(bool (*f)(Utils::Point<T>))
//	{
//		userCheck=f;
//	}

	template <class T>
    std::pair<Utils::Point<T>, int>  RRT<T>::findClosestNode(Utils::Point<T> cur,int direction)
	{
        //转向方向direction
		double min_dist=INT_MAX;
		Utils::Point<T> closest;
		for(int i=0;i<tree.size();i++)
		{
			////std::cout<<"Itering the tree to find closest Node"<<std::endl;
            if (direction==0){//直行
                if (((cur.x-tree[i].first.x)*(1)+(cur.y-tree[i].first.y)*(0))/dist(tree[i].first,cur)>0.5){//限制方向
                    if(dist(tree[i].first,cur) < min_dist)
                    {
                        min_dist=dist(tree[i].first,cur);
                        closest=tree[i].first;
                    }
                }
            }
            else if(direction==1){//左转
                if (((cur.x-tree[i].first.x)*(1)+(cur.y-tree[i].first.y)*(-1))/1.414/dist(tree[i].first,cur)>0.5){//限制方向
                    if(dist(tree[i].first,cur) < min_dist)
                    {
                        min_dist=dist(tree[i].first,cur);
                        closest=tree[i].first;
                    }
                }
            }
            else if(direction==2){//右转
                if (((cur.x-tree[i].first.x)*(1)+(cur.y-tree[i].first.y)*(1))/1.414/dist(tree[i].first,cur)>0.5){//限制方向
                    if(dist(tree[i].first,cur) < min_dist)
                    {
                        min_dist=dist(tree[i].first,cur);
                        closest=tree[i].first;
                    }
                }
            }
		}
		return std::make_pair(closest,1);
	}

	template <class T>
    Utils::Point<T> RRT<T>::generatePoint(int direction)
	{
		Utils::Point<T> temp;
		int signX,signY;

		if(rand()%2==0)
			signX=-1;
		else
			signX=1;
		if(rand()%2==0)
			signY=-1;
		else
			signY=1;

		temp.x = origin.x + signX* ( rand() % (int)halfDimensionX );
		temp.y = origin.y + signY* ( rand() % (int)halfDimensionY );

        Utils::Point<T> closest=findClosestNode(temp,direction).first;
		double theta = atan2(temp.y-closest.y,temp.x-closest.x);

		Utils::Point<T> next;
		next.x=closest.x+stepLength*cos(theta);
		next.y=closest.y+stepLength*sin(theta);
		//std::cout<<"Point Generated = "<<temp.x<<","<<temp.y<<std::endl;
		return next;
	}

	template <class T>
    Utils::Point<T> RRT<T>::generateBiasedPoint(int which,int direction)
	{
        Utils::Point<T> closest=findClosestNode(endPoint,direction).first;
		double theta = atan2(endPoint.y-closest.y,endPoint.x-closest.x);

		Utils::Point<T> next;
		next.x=closest.x+stepLength*cos(theta);
		next.y=closest.y+stepLength*sin(theta);
		//std::cout<<"Biased Point Generated = "<<next.x<<","<<next.y<<std::endl;
		return next;
	}

	template <class T>
    bool RRT<T>::checkPoint(Utils::Point<T> next, vector<obstacle> obs_info)
	{
        for (int i=0;i<obs_info.size();i++){
            if (abs(next.x-obs_info[i].pos_z)<obs_info[i].width/2+2 & abs(next.y-obs_info[i].pos_x)<obs_info[i].width+2){
                return false;
            }
        }
        return true;
	}

	template <class T>
	std::pair <Utils::Point <T>,Utils::Point <T> > RRT<T>::treeComplete(int arr[1])
	{
		//std::cout<<"Checking if tree is complete? "<<std::endl;
		//std::cout<<"tree size = "<<tree.size()<<std::endl;
		int min_dist=INT_MAX;
		for(int i=0;i<tree.size();i++)
		{
			double dis= dist(tree[i].first,endPoint);
			if(dis < min_dist)
				min_dist=dis;
			if(dis < stepLength )
			{
				return std::make_pair(tree[i].first,endPoint);
			}
		}
		//std::cout<<"Min Distance In this iteration = "<<min_dist<<std::endl;
		return std::make_pair(endPoint,endPoint);
	}

	template <class T>
	void RRT<T>::setBiasParameter(unsigned int param)
	{
		biasParameter=param;
	}

	template <class T>
	void RRT<T>::generatePath(Utils::Point<T> first,Utils::Point<T> last)
	{
		Utils::Point<T> cur=last;
		pathPoints.push_back(cur);
		while(cur!=first || cur!=startPoint)
		{
			Utils::Point<T> parent= getParent(cur);
			//std::cout<<"current : "<<cur.x<<","<<cur.y<<"| parent : "<<parent.x<<","<<parent.y<<std::endl;
			pathPoints.push_back(parent);
			cur=parent;
		}
	}

	template <class T>
	Utils::Point<T> RRT<T>::getParent(Utils::Point<T> cur)
	{
		for(int i=0;i<tree.size();i++)
		{
			if(tree[i].first==cur)
				return tree[i].second;
		}
	}

	template <class T>
	double RRT<T>::dist(Utils::Point<T> a,Utils::Point<T> b)
	{
		return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
	}
}
