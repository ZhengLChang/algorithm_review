#include <iostream>
#include <vector>

using namespace std;

class Solution{
public:
    Solution(){
    }
    void operator=(Solution &) = delete;
    int minPathSum(vector<vector<int> >& grid)
    {
        vector<vector<int> > dp = grid;
        int width = dp.size();
        int height = 0;
        if(width <= 0)
        {
            return 0;
        }
        height = dp[0].size();
        for(int i = 1; i < width; ++i)
        {
            dp[i][0] = dp[i - 1][0] + dp[i][0];
        }
        for(int j = 1; j < height; ++j)
        {
            dp[0][j] = dp[0][j - 1] + dp[0][j];
        }
        for(int i = 1; i < width; ++i)
        {
            for(int j = 1; j < height; j++)
            {
                dp[i][j] = min(dp[i - 1][j], dp[i][j  - 1]) + dp[i][j];
            }
        }
        return dp[width - 1][height - 1];
    }
    int get_max_path(vector<vector<int> >& grid)
    {
        /*
        vector<vector<int> > path = {
            {3, 2, 1},
            {4, 1000, 100000},
            {7, 8, 9}
        };
        */
            /*
        int path[3][3] = {
            {3, 2, 1},
            {4, 1000, 100000},
            {7, 8, 9}
        };
        */
        vector<vector<int> > path_arr = grid;
        for(int i = 1; i < path_arr.size(); ++i)
        {
            for(int j = 1; j < path_arr[0].size(); ++j)
            {
                path_arr[i][j] = 0;
            }
        }
        for(int i = 1; i < path_arr.size(); ++i)
        {
            path_arr[i][0] = path_arr[i - 1][0] + grid[i][0];
        }
        for(int j = 1; j < path_arr[0].size(); ++j)
        {
            path_arr[0][j] = path_arr[0][j - 1] + grid[0][j];
        }
        for(int i = 0; i < path_arr.size(); ++i)
        {
            for(int j = 0; j < path_arr[0].size(); ++j)
            {
                cout << path_arr[i][j] << " ";
            }
            cout << endl;
        }
        for(int i = 1; i < path_arr.size(); ++i)
        {
            for(int j = 1; j < path_arr[0].size(); ++j)
            {
                path_arr[i][j] = min(path_arr[i - 1][j] + grid[i][j], path_arr[i][j - 1] + grid[i][j]);

            }
        }
        cout << "================" << endl;
        for(int i = 0; i < path_arr.size(); ++i)
        {
            for(int j = 0; j < path_arr[0].size(); ++j)
            {
                cout << path_arr[i][j] << " ";
            }
            cout << endl;
        }
        return path_arr[path_arr.size() - 1][path_arr[0].size() - 1];
    }
};

int main()
{
    Solution obj;
    vector<vector<int> > path = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1},
    };
    cout << obj.minPathSum(path) << endl;
        for(int i = 0; i < path.size(); ++i)
        {
            for(int j = 0; j < path[0].size(); ++j)
            {
                cout << path[i][j] << " ";
            }
            cout << endl;
        }

    return 0;
}







