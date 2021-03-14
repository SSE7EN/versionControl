# Version Control System

this is a base version control system.
Keeps the history of the changes made,
along with the ability to change the version.

Stores file versions as a binary whose value is hashed (md5)
Then, when trying to save, both hashes are compared to determine if a change has been made 



## Run

The program is run from the command line with the appropriate
switch:
`
	initializing base folder:
	vcInit
	returns data about the current project:
	vcProjectInfo
	returns data about the current project:
	vcCreateProject -n project name -d description
	change of the current project:
	vcCheckout -n project name
	save version:
	vcPush -f filename -d description
	version download:
	vcPull -f file to write -id version id
	returns all versions of the project:
	vcGetVersions  
`
