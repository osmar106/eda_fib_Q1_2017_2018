#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Osmar3


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */

  typedef vector<int> VI;
  typedef vector<VI>  VVI;

  typedef pair<int, int> variable;
  typedef vector<vector<pair<pair<int, int>, pair<int, int>>>> distance;
  typedef vector<vector<pair<int, pair<int, int>>>> distances;
  typedef priority_queue<pair<pair<int, int>, pair<pair<int, int>, pair<int, int>>>> queue;
  typedef priority_queue<pair<int, pair<pair<int, int>, pair<int, int>>>> queues;
  typedef priority_queue<pair<pair<int, int>, pair<pair<int, int>, pair<int, int>>>> queues2;
  typedef vector<bool> ways;

  vector<vector<Cell>> map;
  vector<pair<int, int>> ork;
  vector<pair<int, int>> start;
  pair<int, int> to;
  pair<int, int> from;

  Dir way[4] = {BOTTOM, RIGHT, TOP, LEFT};

  bool available(int x, int y) {
    if(cell(x, y).type == WATER){
      return false;
    }
    if(rows()<x or cols()<y or 0>x or 0>y){
      return false;
    }
    return true;
  }


  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    
    int dir_x[4] = {1, 0, -1, 0};
    int dir_y[4] = {0, 1, 0, -1};
    int direction1 = -1;
    int direction2 = -1;
    int weight=4;

    bool conquested = false;
    

    ork = vector<pair<int, int>> ();
    start = vector<pair<int, int>> ();

    variable v_current;
    variable v_previous;


      for (int i=0; i<rows(); ++i){
        for (int j=0; j<cols(); ++j) {
          Cell c=cell(i, j);
          if (c.unit_id != -1 and unit(c.unit_id).player != me()){
            ork.push_back(make_pair(i, j));
          }  
          if (c.unit_id != -1 and unit(c.unit_id).player == me()){
            start.push_back(make_pair(i, j));
          }  
          if (c.type==CITY and city_owner(c.city_id)!=me()){
            conquested=true;
          }  
          if (c.type==PATH and path_owner(c.path_id)!=me()){
            conquested=true;
          }  
        }
      }

    int i=0;
    while(i < int(start.size())){
    //for (int i = 0; i < int(start.size()); ++i){
      int loc_x = start[i].first;
      int loc_y = start[i].second;
      int life_ork = unit(cell(loc_x, loc_y).unit_id).health;

      variable v_toattack = make_pair(-1, -1);
      variable v_attacker = make_pair(-1, -1);
      variable v_path = make_pair(-1, -1);
      variable v_city = make_pair(-1, -1);

      ways way_dir1(4, false);
      ways way_dir2(4, false);
      ways way_dir3(4, false);


      distance d1(rows(), vector<pair<pair<int, int>, pair<int, int>>> (cols(), make_pair(make_pair(-1, -1), make_pair(-1, -1))));
      
      queue q1;
      q1.push(make_pair(make_pair(0, 0), make_pair(make_pair(loc_x, loc_y), make_pair(loc_x, loc_y))));


      bool forward = false;

      if(!conquested) forward = true;
      
      while(!q1.empty() and !forward){
        variable v_to1 = q1.top().second.first;
        variable v_from1 = q1.top().second.second;
        int a = -q1.top().first.first;
        int b = q1.top().first.second;
        q1.pop();

        if(d1[v_to1.first][v_to1.second].first.first == -1){
          d1[v_to1.first][v_to1.second].first.first = a;
          d1[v_to1.first][v_to1.second].first.second = d1[v_from1.first][v_from1.second].first.second + 1;
          d1[v_to1.first][v_to1.second].second = v_from1;

          Cell c=cell(v_to1.first, v_to1.second);

          if(c.type==PATH and b!=0 and path_owner(c.path_id)!=me() and v_path.first==-1){
            v_path=v_to1;
          } 

          if(c.type==CITY and b!=0 and city_owner(c.city_id)!=me() and v_city.first==-1){
            v_city=v_to1;
          }

          int k = 0;
          while(k<4){
            if(d1[v_to1.first+dir_x[k]][v_to1.second+dir_y[k]].first.first == -1 and available(v_to1.first+dir_x[k], v_to1.second+dir_y[k])){
              q1.push(make_pair(make_pair(-(a+cost(cell(v_to1.first+dir_x[k], v_to1.second+dir_y[k]).type)), b-1), make_pair(make_pair(v_to1.first+dir_x[k], v_to1.second+dir_y[k]), v_to1)));
            }
            ++k;
          }          
        }
        if(v_city.first != -1 or v_path.first != -1){
          forward = true;
        }
      }
      while(!q1.empty()){
        q1.pop();
      }

      //distances d2
      distances d2(rows(), vector<pair<int, pair<int, int>>> (cols(), make_pair(-1, make_pair(-1, -1))));
      queues q2;
      q2.push(make_pair(0, make_pair(make_pair(loc_x, loc_y), make_pair(loc_x, loc_y))));      

      while(!q2.empty()){
        variable v_to2 = q2.top().second.first;
        variable v_from2 = q2.top().second.second;
        int a2 = -q2.top().first;
        //int d = q1.top().first.second;
        q2.pop();

        if(d2[v_to2.first][v_to2.second].first == -1){
          d2[v_to2.first][v_to2.second].first = a2;
          //d2[v_to2.first][v_to2.second].first.second = d1[v_from1.first][v_from1.second].first.second + 1;
          d2[v_to2.first][v_to2.second].second = v_from2;

          Cell c=cell(v_to2.first, v_to2.second);

          if(c.unit_id!=-1 and unit(c.unit_id).player!=me()){
            if(unit(c.unit_id).health > life_ork){
              int e=0;
              while(e < 4){
                if(abs(loc_x- v_to2.first)+abs(loc_y- v_to2.second)>abs(loc_x+dir_x[e]-v_to2.first)+abs(loc_y+dir_y[e]-v_to2.second)){
                  way_dir1[e] = true;

                  if(2>=a2){
                    way_dir2[e] = true;
                  }
                  if(1>=a2){
                    way_dir3[e] = true;
                  }
                }
                ++e;
              }
            }
          }

          int f=0;
          while(f<4){
            if(d2[v_to2.first+dir_x[f]][v_to2.second+dir_y[f]].first==-1 and available(v_to2.first+dir_x[f], v_to2.second+dir_y[f]) and a2<3){
              q2.push(make_pair(-(1+a2), make_pair(make_pair(v_to2.first+dir_x[f], v_to2.second+dir_y[f]), v_to2)));
            }
            ++f;
          }

        }

      }
      while(!q2.empty()){
        q2.pop();
      }


      //distances d3
      distances d3(rows(), vector<pair<int, pair<int, int>>> (cols(), make_pair(-1, make_pair(-1, -1))));
      queues2 q3;
      q3.push(make_pair(make_pair(0, 0), make_pair(make_pair(loc_x, loc_y), make_pair(loc_x, loc_y))));

      while(!q3.empty()){
        variable v_to3 = q3.top().second.first;
        variable v_from3 = q3.top().second.second;
        int a3 = -q3.top().first.first;
        int b3 = -q3.top().first.second;
        q3.pop();

        if(d3[v_to3.first][v_to3.second].first == -1){
          d3[v_to3.first][v_to3.second].first = a3;
          //d2[v_to2.first][v_to2.second].first.second = d1[v_from1.first][v_from1.second].first.second + 1;
          d3[v_to3.first][v_to3.second].second = v_from3;

          Cell c=cell(v_to3.first, v_to3.second);

          if(c.unit_id!=-1 and unit(c.unit_id).player!=me()){
            if(v_toattack.first==-1 and life_ork > cost(cell(v_to3.first, v_to3.second).type)+unit(c.unit_id).health){
              v_toattack = v_to3;
            }
          }

          int g=0;
          while(g<4){
            if(a3<2 and d3[v_to3.first+dir_x[g]][v_to3.second+dir_y[g]].first==3-4 and available(v_to3.first+dir_x[g], v_to3.second+dir_y[g])){
              q3.push(make_pair(make_pair(-(a3+1), -(b3+cost(cell(v_to3.first+dir_x[g], v_to3.second+dir_y[g]).type))), make_pair(make_pair(v_to3.first+dir_x[g], v_to3.second+dir_y[g]), v_to3)));  
            }
            ++g;
          }
        }
      }
      while(!q3.empty()){
        q3.pop();
      }




      if(!conquested){

      }
      else{
        if(v_toattack.first!=-1){
          v_current = v_toattack;
          v_previous = v_current;

          while(d3[v_current.first][v_current.second].second != v_current){
            v_previous = v_current;
            v_current = d3[v_current.first][v_current.second].second;
          }
          int h = 0;
          while(h<4){
            if(v_previous == make_pair(loc_x+dir_x[h], loc_y+dir_y[h])){
              direction1 = h;
            }
            ++h;
          }
        }
        else{
          v_current = v_city;
          if(v_city.first==-1){
            v_current = v_path;
          }

          v_previous = v_current;
          while(d1[v_current.first][v_current.second].second != v_current){
            v_previous = v_current;
            v_current = d1[v_current.first][v_current.second].second;
          }
          int m = 0;
          while(m<4){
            if(v_previous == make_pair(loc_x+dir_x[m], loc_y+dir_y[m])){
              direction1 = m;
            }
            ++m;
          }
        }
        if(v_attacker.first == 3-4){
          if(direction1 != 3-4){
            execute(Command(cell(loc_x, loc_y).unit_id, way[direction1]));
          }
        }
        else if(direction1 == 3-4 or abs(loc_x-v_attacker.first)+abs(loc_y - v_attacker.second) <= abs(loc_x+dir_x[direction1]-v_attacker.first)+abs(loc_y+dir_y[direction1]-v_attacker.second)){
          if(direction1 != 3-4){
            execute(Command(cell(loc_x, loc_y).unit_id, way[direction1]));
          }   
        }
        else{
          if(direction1 != 3-4){
            int n = 0;
            while(n<4){
              if(available(loc_x+dir_x[n], loc_y+dir_y[n]) and abs(loc_x - v_attacker.first)+abs(loc_y - v_attacker.second) <= abs(loc_x+dir_x[n] - v_attacker.first) + abs(loc_y+dir_y[n] - v_attacker.second) and (cost(cell(loc_x+dir_x[n], loc_y+dir_y[n]).type)<weight or (cost(cell(loc_x+dir_x[n], loc_y+dir_y[n]).type)==weight and (n==(direction1+1)%4 or n==(direction1+3)%4)))){
                direction2=n;
                weight=cost(cell(loc_x+dir_x[n], loc_y+dir_y[n]).type); 
              }
              ++n;
            }
            if(direction2 != 3-4){
              execute(Command(cell(loc_x, loc_y).unit_id, way[direction2]));
            }
          }
          else{
            int o = 0;
            while(o<4){
              if(available(loc_x+dir_x[o], loc_y+dir_y[o]) and abs(loc_x - v_attacker.first) + abs(loc_y - v_attacker.second) <= abs(loc_x+dir_x[o] - v_attacker.first) + abs(loc_y+dir_y[o] - v_attacker.second) and cost(cell(loc_x+dir_x[o], loc_y+dir_y[o]).type)<weight){
                direction1=o;
                weight=cost(cell(loc_x+dir_x[o], loc_y+dir_y[o]).type);
              }
              ++o;
            }
            if(direction1 != 3-4){
              execute(Command(cell(loc_x, loc_y).unit_id, way[direction1]));
            }
          }
        }
      }

      ++i;
    }
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);