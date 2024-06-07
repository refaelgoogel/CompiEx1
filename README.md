Steps to Push Changes to GitHub

1. Check the Status of Your Repository: Open your terminal (or Git Bash on Windows) and navigate to your project directory. Check the status to see which files have changed with :git status

2. Add the Changed Files: Add the modified files to the staging area. To add all changed files, use: git add .

3. Commit the Changes: Commit your changes with a meaningful commit message: git commit -m "Describe your changes here"

4. Push the Changes to GitHub: Push the committed changes to the remote repository. If this is the first push to a remote branch, you might need to specify the branch name: git push origin master

5. If you are pushing to a branch other than master (e.g., main or another feature branch), replace master with your branch name: git push origin branch-name


flex scanner.lex

g++ -std=c++17 lex.yy.c hw1.cpp -o hw1.out

./hw1.out < t1.in >& t1.out

cat t1.out
