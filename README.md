# Version Control System

this is a base version control system.
Keeps the history of the changes made,
along with the ability to change the version.

Stores file versions as a binary whose value is hashed (md5)
Then, when trying to save, both hashes are compared to determine if a change has been made 



## Run

The program is run from the command line with the appropriate
switch:
<br/>
	initializing base folder:
	vcInit <br/>
	returns data about the current project:
	vcProjectInfo <br/>
	returns data about the current project:
	vcCreateProject -n project name -d description <br/>
	change of the current project:
	vcCheckout -n project name <br/>
	save version:
	vcPush -f filename -d description <br/>
	version download:
	vcPull -f file to write -id version id <br/>
	returns all versions of the project:
	vcGetVersions  <br/>

