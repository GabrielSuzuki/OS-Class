#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


int main()
{
	/* The command buffer */
	string cmdBuff;

	/* The ID of the child process */
	pid_t pid = 1;

	/* Keep running until the user has typed "exit" */
	int numLines = 0;

	ifstream in("urls.txt");
	string urlstring;
	/*if (in.is_open())
  {
	while ( getline (in,urlstring) )
	{
	  //cout << urlstring << '\n';
			++numLines;
	}
	in.close();
  }*/


	do {

		/* Prompt the user to enter the command */
		cerr << "cmd>";
		cin >> cmdBuff;
		/* If the user wants to exit */
		if (cmdBuff != "exit")
		{
			/* TODO: Create a child */
			if (in.is_open())
			{
				while (getline(in, urlstring) && pid > 0)
				{
					//cout << urlstring << '\n';
					pid = fork();
					cout << "forking child process: pid = " << pid << endl;
					if (pid < 0) {//error occured
						fprintf(stderr, "Fork Failed");
						return 1;
					}
					else if (pid == 0) {//child process
							  //cout << urlstring;

						execlp("/usr/bin/wget", "wget", urlstring.c_str(), NULL);
						cout << "Child Complete";
					}
					/*** TODO: If I am child, I will do this: ****/
					/* Call execlp() to replace my program with that specified at the command line.
					 * PLEASE NOTE: YOU CANNOT PASS cmdBuff DIRECTLY to execlp(). It is because
					 * cmdBuff is an object of type string (i.e., a class) and execlp() expects
					 * an array of characters.  However, you can pass cmdBuff.c_str(), which will
					 * return an array of characters representation of the string object.
					 *
					 * Also, please do not forget to error check your exelp() system calls.
					 */
					else {//parent process
						numLines++;
						cout << "numLines = " << numLines << endl;
					}
				}

				in.close();
				if (pid > 0) {
					for (int i = 0; i < numLines; i++) {
						wait(NULL);
					}
				}
			}
			else cout << "Unable to open file";


		}

		/* TODO: Error check to make sure the child was successfully created */

	}
	/*** TODO: If I am a parent, I will do the following ***?
	/* Wait for the child process to terminate */
	while (cmdBuff != "exit" && pid != 0);
	return 0;
}
