# generate help with sspar snippet
usage() {
    echo "Usage: build.sh [commands]"
    echo ""
    echo "This script builds project"
    echo ""
    echo "Parameters:"
    echo " -r, --rebuild        Rebuild whole project"
    echo " -h, --help           Print this help"
    echo ""
}

REBUILD=false

while [ ! -z $1 ]
do
    case "$1" in
        --rebuild | -r)
            REBUILD=true
            ;;
        --help | -h)
            usage  # generate usage with ssusa snippet
            exit 0;;
        *)
            usage
            exit 0;;
    esac
    shift  # it removes first argument from list of params
done

if [ "$REBUILD" = true ]
then
    if [ -d ../build ]
    then
        rm -fr ../build/
    fi
fi

if [ ! -d ../build ]
then
    mkdir ../build
fi

cd ../build

cmake ..

make -j 2

