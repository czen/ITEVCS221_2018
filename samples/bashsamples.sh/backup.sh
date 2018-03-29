BACKUPDIR=$HOME/bash_training/backup
WORKDIR=$HOME/bash_training/work
DATE=`date +%Y_%m_%d.tar`
ARCHIVE=$BACKUPDIR/$DATE

mkdir -p $BACKUPDIR

for FILE in $(find "$WORKDIR" -type f -mtime -1 2> /dev/null); do
echo " Adding $FILE"
tar -uf "$ARCHIVE" "$FILE"
done