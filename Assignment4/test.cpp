#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


int main(int argc, char* argv[])
{
	/* The command buffer */
	string cmdBuff;

	/* The ID of the child process */
	pid_t pid = 1;

	string filename;
	string key;
	int n;
	int found = 1;
	int exit_status;
	int count = 0;
	vector<string> stringlist;

	filename = argv[1];
	key = argv[2];
	n = stoi(argv[3]);
	/* Keep running until the user has typed "exit" */
	int temp = 0;

	ifstream in(filename);
	string stringline;

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
				while (getline(in, stringline))//read each line
				{
					stringlist.push_back(stringline);
				}
			}
			else cout << "Unable to open file";

			in.close();//close file
			//vector<string>::iterator it = stringlist.begin();
			string it;
			while (temp < n) {
				it = stringlist.at(temp);
				pid = fork();

				if (pid < 0) {
					fprintf(stderr, "Fork Failed");
					return 1;
				}
				else if (pid == 0) {//child
					exit_status = 0;
					if (it == key) {
						exit_status = 0;
					}
					else {
						exit_status = 1;
					}
					return exit_status;
				}
				else {//parent
					if (wait(&exit_status) < 1) {
						perror("wait");
						exit(-1);
					}

					if (WEXITSTATUS(exit_status) == 0) {
						found = 0;
					}
					if (found == 0) {
						count++;
					}
				}

				//++it;
				temp++;
			}
			if (found == 0 && temp == n) {
				cout << "string has been found by " << count << " children";
				return 0;
			}
			cout << "No string found";
			return 0;
		}
	} while (cmdBuff != "exit" && pid != 0);
	return 0;
}
