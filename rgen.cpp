// an example of reading random numbers from /dev/urandom
// https://stackoverflow.com/questions/35726331/c-extracting-random-numbers-from-dev-urandom
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

unsigned int rand_street_num ( unsigned int k )
{
    // open /dev/urandom to read
    ifstream urandom("/dev/urandom");

    // check that it did not fail
    if (urandom.fail()) {
        cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int rand = 3;
    urandom.read((char*)&rand, sizeof(unsigned int));
    rand = rand % (k-2+1) +2;
    urandom.close();
    return (unsigned int) rand;

}

unsigned int rand_line_segment_num (unsigned int k)
{
    // open /dev/urandom to read
    ifstream urandom("/dev/urandom");

    // check that it did not fail
    if (urandom.fail()) {
        cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int rand = 3;
    urandom.read((char*)&rand, sizeof(unsigned int));
    rand = rand % (k-1+1) + 1;
    urandom.close();
    return (unsigned int) rand;
}

unsigned int rand_wait_num (unsigned int k)
{
    // open /dev/urandom to read
    ifstream urandom("/dev/urandom");

    // check that it did not fail
    if (urandom.fail()) {
        cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int time = 3;
    urandom.read((char*)&time, sizeof(unsigned int));
    time = time % (k-5+1) + 5;
    urandom.close();
    return (unsigned int) time;
}

int rand_coordinate_value (unsigned int k)
{
    // open /dev/urandom to read
    ifstream urandom("/dev/urandom");

    // check that it did not fail
    if (urandom.fail()) {
        cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int rand = 3;
    urandom.read((char*)&rand, sizeof(int));
    rand = rand % (k+k);
    int out= rand - k ;
    urandom.close();
    return out;
}

void generate_streets( vector<string> &street , unsigned int street_num)
{
    string name = "a";
    for (unsigned int i=0; i < street_num; i++)
    {
        street.push_back(name);
        name = name +"a";
    }

}

bool check_zerolength(vector<int> &coord, int xcoord, int ycoord){

  int last_ycoord_index = coord.size();
  //check no zero length line segment

  if(last_ycoord_index != 0 && last_ycoord_index != 1){
  if(xcoord == coord[last_ycoord_index-2] && ycoord == coord[last_ycoord_index-1]){
    return false;
  }
}
  return true;
}
//2,2,5,5,5,6,5,5 this works - not intersecting even when 1 endpoint is same
bool isIntersecting(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    return (((x3-x1)*(y2-y1) - (y3-y1)*(x2-x1))
            * ((x4-x1)*(y2-y1) - (y4-y1)*(x2-x1)) < 0)
            &&
           (((x1-x3)*(y4-y3) - (y1-y3)*(x4-x3))
            * ((x2-x3)*(y4-y3) - (y2-y3)*(x4-x3)) < 0);
}

bool check_intersection(vector<int> &coord, int xcoord, int ycoord){
  int last_ycoord_index = coord.size();
  bool intersect = false;
  for(unsigned int j = 0 ; j < coord.size() ; j = j + 2){
    intersect = isIntersecting(xcoord, ycoord, coord[last_ycoord_index-2], coord[last_ycoord_index-1], coord[j] ,coord[j+1], coord[j+2], coord[j+3] );
    if(intersect){
      return false;
    }
  }
  return true;
}

bool check_overlap(vector<int> &coord, int xcoord, int ycoord){

    int k = coord.size();
	//cout << "size " << k;
    int x1;
    int x2;
    int y1;
    int y2;

    if(k-4 >= 0 && k-3 >= 0 && k-2 >= 0 && k-1 >= 0){
      x1 = coord[k-4];
      y1 = coord[k-3];
      x2 = coord[k-2];
      y2 = coord[k-1];
    }
    //cout << x1 << " " << y1 << " " << x2 << " " << y2 <<'\n';
    //x2 = k - 2, y2 = k - 1, x1 = k - 4 , y1 = k-3

        int dxc = xcoord - x1;
        int dyc = ycoord - y1;

        int dxl = x2 - x1;
        int dyl = y2 - y1;

        int cross = round(dxc*dyl) - round(dyc*dxl);
        //cout << dxc << " " << dyc << " " <<dxl << " " <<dyl;
        if(cross != 0){
            //check slopes
            return false;
        }

        double m1 = 0;
        if(x2 == x1)//x2 == x1
        {
            //slope is undefined
        }else{
            m1 = (y2 - y1)/(x2 - x1);
        }

        double m2 = 0;
        if(xcoord == x2){
            //slope is undefined
        }else{
            m2 = (ycoord - y2)/(xcoord - x2);
        }

        if(abs(dxl) >= abs(dyl)){
            if(dxl > 0){
                return (x1 <= xcoord && xcoord <= x2) || (m1 == m2);
            }else{
                return (x2 <= xcoord && xcoord <= x1) || (m1 == m2);
            }
        }else{
            if(dyl > 0){
                return (y1 <= ycoord && ycoord <= y2) || (m1 == m2);
            }else{

                return (y2 <= ycoord && ycoord <= y1) || (m1 == m2);
            }
        }
    return true;
}

bool check_if_overlap(int x1,int y1,int x2,int y2,int x3,int y3,int xcoord,int ycoord){
  double m1 = 0;
  if(x1 == x2){
    //slope is undefined
  }else{
    m1 = (y2-y1)/(x2-x1);
  }

  double m2 = 0;
  if(xcoord == x3){
    //slope is undefined
  }else{
    m2 = (ycoord-y3)/(xcoord-x3);
  }

  if(m1 == m2){
    //check if xcoord yccoord lies between the line segment
    int dxc = xcoord - x1;
    int dyc = ycoord - y1;

    int dxl = x2 - x1;
    int dyl = y2 - y1;

    int cross = round(dxc*dyl) - round(dyc*dxl);

    if(cross != 0){
        return false;
    }

    if(abs(dxl) >= abs(dyl)){
        if(dxl > 0){
            return (x1 <= xcoord && xcoord <= x2);
        }else{
            return (x2 <= xcoord && xcoord <= x1);
        }
    }else{
        if(dyl > 0){
            return (y1 <= ycoord && ycoord <= y2);
        }else{
            return (y2 <= ycoord && ycoord <= y1);
        }
    }

  }else{
    return false;
  }
return false;
}

bool check_overlap_allstreets(vector< vector<int> > &allstreets, vector<int> &coord, int xcoord, int ycoord){
    int k = coord.size();
    if(k>=2){
    	int x3 = coord[k-2];
    	int y3 = coord[k-1];
	

    vector<int> v;
    for(unsigned int i = 0 ; i < allstreets.size() ; i++){
      for(unsigned int j = 0 ; j <= allstreets[i].size() - 4 ; j = j+2){

         int x1 = allstreets[i][j];
         int y1 = allstreets[i][j+1];
         int x2 = allstreets[i][j+2];
         int y2 = allstreets[i][j+3];

         bool isOverlap = check_if_overlap(x1,y1,x2,y2,x3,y3,xcoord,ycoord);
         if(isOverlap){
           return true;
         }
      }
    }
}
    return false;
}



int main(int argc, char** argv) {

  unsigned int sd = 10;
  unsigned int ld = 5;
  unsigned int wd = 5;
  unsigned int cd = 20;
  vector<string> street; //street names
  unsigned int l_num;
  vector<int> street_line_num;
  vector< vector<int> > street_coord;
 //cout << "argc : " << argc;
  //unsigned int arg_n = argc;
  for (int i = 0; i < argc ; i++){

      stringstream ssValue;
      //cout << argv[i] << "\n ";
      if (std::string(argv[i]) == "-s"){
      ssValue << argv[i+1];
      ssValue  >> sd;
      }else if(string(argv[i]) == "-n"){
      ssValue << argv[i+1];
      ssValue  >> ld;
      }else if(string(argv[i]) == "-l"){
      ssValue << argv[i+1];
                  ssValue  >> wd;
      }else if(string(argv[i]) == "-c"){
      ssValue << argv[i+1];
                  ssValue  >> cd;

      }
  }

  unsigned int wait_time = rand_wait_num(wd);
  unsigned int num_street = rand_street_num(sd);
  generate_streets(street, num_street);
  //cout << "no. of streets"<<num_street<<'\n';
  unsigned int error_flag = 0;
  unsigned int count = 0;
for (unsigned int j = 0; j < num_street; j++)
{
       l_num = rand_line_segment_num(ld);
       street_line_num.push_back(l_num);
}
//generate line segments for each streets

while(!cin.eof()){
street_coord.clear();
//street_line_num.clear();
count++;
for (unsigned int j = 0; j < num_street; j++)
   {
      // l_num = rand_line_segment_num(ld);
      // street_line_num.push_back(l_num);
      // cout << "line -" << l_num << '\n';
       int m = street_line_num[j];
       int x_coord;
       int y_coord;
       vector<int> coord;

       while(m >= 0){
         x_coord = rand_coordinate_value(cd);
         y_coord = rand_coordinate_value(cd);

        bool length_check = true;
        length_check = check_zerolength(coord,x_coord,y_coord);
        bool intersect_check = true;
        bool isOverlap = false;
        bool any_partial_overlap = false;

        if( m <= l_num - 2){ //one segment is already added
          intersect_check = check_intersection(coord, x_coord, y_coord);
          isOverlap = check_overlap(coord, x_coord, y_coord);
          if(street_coord.size() > 1){
            any_partial_overlap = check_overlap_allstreets(street_coord, coord, x_coord, y_coord);
          }
        }

         if(length_check && intersect_check && !isOverlap && !any_partial_overlap){
           coord.push_back(x_coord);
           coord.push_back(y_coord);
           m--;
           error_flag = 0;
         }else{
          // cout << "Error  " << x_coord << "  " << y_coord << '\n';
           if(error_flag == 25){
             cout << "Error: failed to generate valid inputs for 25 simultaneous attempts";
             exit(1);
           }
           error_flag = error_flag + 1;
         }
       }
       street_coord.push_back(coord);
   }

  /*for(int k = 0 ; k < street_line_num.size() ; k++){
    cout << street_line_num[k] << '\n';
  }*/
  vector< vector<int> >::iterator row;
  vector<int>::iterator col;

  if(count != 1){
	string remove_streets;
	for(unsigned int a = 0 ; a < street.size(); a++){
		remove_streets = "r \""+street[a]+"\"";
		cout << remove_streets << endl;
	}
}

     //a output
      string add_street_output ;
      for(unsigned int i = 0 ; i < street_coord.size() ; i++){
          add_street_output =  "a \"" +  street[i] + "\" ";
          string coordinates ;
          for(unsigned int j = 0; j < street_coord[i].size() ; j=j+2){
	    stringstream x;
	    stringstream y;
	    x << street_coord[i][j];
	    y << street_coord[i][j+1];
            coordinates =coordinates+"("+ x.str() + "," + y.str() + ")";
          }
          add_street_output = add_street_output + coordinates;
      	  cout << add_street_output << endl;
	}
      //cout << add_street_output;
      cout << "g" << endl;

//  generate_output(street_coord, street);
  usleep(wait_time*1000000);
}
  return 0;
}
