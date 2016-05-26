# generate help with sspar snippet
usage() {
    echo "Usage: run.sh [commands]"
    echo ""
    echo "This script runs project if it has been build"
    echo ""
    echo "Parameters:"
    echo " -h, --help           Print this help"
    echo ""
}

while [ ! -z $1 ]
do
    case "$1" in
        --help | -h)
            usage  # generate usage with ssusa snippet
            exit 0;;
        *)
            usage
            exit 0;;
    esac
shift  # it removes first argument from list of params
done


../build/source/object_tracking

