INTRODUCTION
------------

this project is about handling pipes

I had to implement unix logic by recreating pipes (as in bash)

UTILISATION
------------

run 'make' to compile

run './pipex infile "(shellcommandwithoptions)" "shellcommand(withoptions)" outfile' to execute

ex. './pipex infile "ls -l" "wc -l" outfile' behaves like: < infile ls -l | wc -l > outfile
