#!/bin/sh

echo "Enter a commit message: ";
read commit_msg;
if [ ! -z "$commit_msg" ]
then
    git add .;
    git commit -m "$commit_msg";
    git push;
    git status;
else
    echo "Empty commit messages are not allowed!";
fi
