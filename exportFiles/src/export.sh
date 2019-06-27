cd ../..
mkdir exportFiles
cp -r build/* exportFiles
tar -zcvf exportFiles.tar.gz exportFiles
git add .
git commit -m "[AUTOMATION] - Updated lookup database."
git push origin master
