#!/bin/bash -e

# work over each commit and append all files in tree to $tempFile
tempFile=$(mktemp)
for commitSHA1 in $(git rev-list --all); do
    git ls-tree -r --long "$commitSHA1" >>"$tempFile"
done

# sort files by SHA1, de-dupe list and finally re-sort by filesize
sort -k3 "$tempFile" | \
    uniq | \
    sort -nr -k4

# remove temp file
rm "$tempFile"