# Setup premake
cd vendor/repos/premake
make -f Bootstrap.mak macosx-clean
make -f Bootstrap.mak osx
cd ../../../

# Prepare GLEW

cd ronin/vendor/repos/GLEW/auto
make
cd ..
make
sudo make install
make clean
cd ../../../../

# Setup ronin project with premake

./vendor/repos/premake/bin/release/premake5 gmake2