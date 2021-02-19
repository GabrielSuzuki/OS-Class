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
				while (getline(in, urlstring) && pid > 0)//read each line
				{
					pid = fork();//fork a child
					cout << "forking child process: pid = " << pid << endl;
					if (pid < 0) {//error occured
						fprintf(stderr, "Fork Failed");
						return 1;
					}
					else if (pid == 0) {//child process

						execlp("/usr/bin/wget", "wget", urlstring.c_str(), NULL);//download url
						cout << "Child Complete";
					}
					else {//parent process
						numLines++;
						cout << "numLines = " << numLines << endl;
					}
				}

				in.close();//close file
				if (pid > 0) {//wait numLines times
					for (int i = 0; i < numLines; i++) {
						wait(NULL);
					}
				}
			}
			else cout << "Unable to open file";
		}
	}
	while (cmdBuff != "exit" && pid != 0);
	return 0;
}
