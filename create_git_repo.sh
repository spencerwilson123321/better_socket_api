#!/bin/sh

# Before running this script, you need to go on github and make a repository that has no files.
# DO NOT add a README or .gitignore file when creating the repository.

echo "Enter the repository name you created on github: (without .git i.e. 'my_project')";
read repo_name;
echo "Enter a commit message for your first commit:";
read commit_msg;
if [ ! -z "$repo_name" ] && [ ! -z "$commit_msg" ]
then
    git init;
    touch .gitignore;
    echo ".*";   
    git add .;
    git commit -m "$commit_msg" 
    git remote add origin git@github.com:spencerwilson123321/"$repo_name".git;
    git push -u origin master;
else
    echo "Repository name and/or commit message cannot be empty strings!";
fi

