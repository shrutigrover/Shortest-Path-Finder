#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <iostream>
#include <stdlib.h>

int main (int argc, char **argv) {
    std::cout << "Replace with your solution for the main "
              << "driver program of Assignment 3\n";
   
	std::vector<pid_t> kids;
	int rgentoa1[2];
	int a1toa2[2]; 
/* Create a pipe. File descriptors for the two ends of the pipe are
 * placed in fds. */
	pipe (rgentoa1);
	pipe(a1toa2);
    pid_t kid;
    kid = fork ();
    if (kid == 0) {
              
	sleep (4);
       // fflush(stdout);
	//close(rgentoa1[0]);
	dup2(rgentoa1[1], STDOUT_FILENO);
        
        close(rgentoa1[1]);

	int rgen = execv ("rgen", argv);
	// execl("/bin/ls", "ls", "-l", nullptr);
  	//   perror ("Error from arie");
  	return rgen;
     }else if(kid < 0){
	std::cerr << "Error: could not fork\n";
	return 1;
     }
	
	kids.push_back(kid);

	kid = fork();
	if(kid == 0){
		close(rgentoa1[1]);

		dup2(rgentoa1[0], STDIN_FILENO);
//	        close(rgentoa1[0]);
  //      	close(rgentoa1[1]);
	
		//fflush(stdout);
		close(a1toa2[0]);

		dup2(a1toa2[1], STDOUT_FILENO);
//		close(a1toa2[0]);
//		close(a1toa2[1]);
	
		char *argvn[3];
		argvn[0] = (char *)"python";
		argvn[1] = (char *)"ece650-a1.py";
		argvn[2] = nullptr;
			
		return execvp("python",argvn);
	}

	close(rgentoa1[0]);
        close(rgentoa1[1]);
	kids.push_back(kid);

 	close(a1toa2[1]);
	dup2(a1toa2[0], STDIN_FILENO);
        //close(a1toa2[0]);
        //close(a1toa2[1]);
	
	int a2 = execv("a2-ece650",argv);
	return a2;
	close(a1toa2[0]);
        close(a1toa2[1]);

	//int res;
        //waitpid(kid, &res, 0);
        //std::cout << "rgen  returned status: " << res << std::endl;
	
	for(int a = 0 ; a < kids.size() ; a++){
		int status;
		kill(kids[a], SIGTERM);
		waitpid(kids[a], &status, 0);
	}
	 return 0;
}
