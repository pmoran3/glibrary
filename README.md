# glibrary

various utility libraries for gemc

## createGLibrary

 - creates a directory with files from the template directory


## TODO

check github action workflows





## Automatic travis push to github

- In GitHub, go to settings and Personal access tokens
- Click Generate a new token and fill in the description. e.g. <your_repo> Travis CI Documentation
- If the repository is public select as scope public_repo. If your repository is private select as scope repo
- Click Generate token
- Copy the generated token

- In Travis CI, go to the repository settings 
- In the Environment Variables section write in the Name field GH_REPO_TOKEN
- Past the copied token in the Value field
- Make sure that the Display value in build log is switched off
 - Click on Add

Create the gh-page branch: 

git checkout --orphan gh-pages
git commit -m "First commit"
git push origin gh-pages
git rm -rf .
git commit -m "Clean start"
git push origin gh-pages
