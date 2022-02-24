../../bin/make.exe clean
if [ $1 = "debug" ]; then
	echo "building for debug ..."
	../../bin/make.exe debug
	CEmu -s ../../bin/clibs.8xg -s bin/CONNECT4.8xp --launch CONNECT4 
else 
	echo "building for production ..."
	../../bin/make.exe
	CEmu -s ../../bin/clibs.8xg -s bin/CONNECT4.8xp --launch CONNECT4 
fi
