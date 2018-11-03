// an example of reading random numbers from /dev/urandom
// https://stackoverflow.com/questions/35726331/c-extracting-random-numbers-from-dev-urandom
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>

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
    for ( int i=0; i < street_num; i++)
    {
        street.push_back(name);
        name = name +"a";
    }

}


/*bool check_partial_overlaps(vector<> allCoord,){
  return false;
}*/

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
  for(int j = 0 ; j < coord.size() ; j = j + 2){
    intersect = isIntersecting(xcoord, ycoord, coord[last_ycoord_index-2], coord[last_ycoord_index-1], coord[j] ,coord[j+1], coord[j+2], coord[j+3] );
    if(intersect){
      return false;
    }
  }
  return true;
}

void generate_output(vector< vector<int> > &street_coord, vector<string> &streets){
      string add_street_output = "";
      for(int i = 0 ; i < street_coord.size() ; i++){
          add_street_output = add_street_output + "a \"" +  streets[i] + "\" ";
          string coordinates ;
          for(int j = 0; j < street_coord[i].size() ; j=j+2){
	    stringstream x;
	    stringstream y;
	    x << street_coord[i][j];
	    y << street_coord[i][j+1];
            coordinates =coordinates+"("+ x.str() + "," + y.str() + ")";
          }
          add_street_output = add_street_output + coordinates + '\n';
      }
      cout << add_street_output << '\n';
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

  for (int i = 0; i < argc; ++i){

      stringstream ssValue;
          cout << argv[i] << "\n ";
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
  cout << "no. of streets"<<num_street<<'\n';
  unsigned int error_flag = 0;
  //generate line segments for each streets
  for (int j = 0; j < num_street; j++)
   {
       l_num = rand_line_segment_num(ld);
       street_line_num.push_back(l_num);
       cout << "line -" << l_num << '\n';
       int m = l_num;
       int x_coord;
       int y_coord;
       vector<int> coord;

       while(m >= 0){
         x_coord = rand_coordinate_value(cd);
         y_coord = rand_coordinate_value(cd);

	      bool length_check = true;
        length_check = check_zerolength(coord,x_coord,y_coord);
        bool intersect_check = true;
        if( m <= l_num - 2){ //one segment is already added
          intersect_check = check_intersection(coord, x_coord, y_coord);
        }
         if(length_check && intersect_check){
           coord.push_back(x_coord);
           coord.push_back(y_coord);
           m--;
           error_flag = 0;
         }else{
           cerr << "Error  " << x_coord << "  " << y_coord << '\n';
           if(error_flag == 25){
             cerr << "Error: failed to generate valid inputs for 25 simultaneous attempts";
             exit(1);
           }
           error_flag = error_flag + 1;
         }
       }
       street_coord.push_back(coord);
   }

  for(int k = 0 ; k < street_line_num.size() ; k++){
    cout << street_line_num[k] << '\n';
  }
  vector< vector<int> >::iterator row;
  vector<int>::iterator col;
  for (row = street_coord.begin(); row != street_coord.end(); row++) {
      cout << "street :";
      for (col = row->begin(); col != row->end(); col++) {
          cout << *col << "  ";
      }
      cout << '\n';
  }
  generate_output(street_coord, street);

  return 0;
}
