./run1 $1 < $1.graphs
header=$(head -1 header.txt)
(head -1 header.txt && cat $1.satinput) > tempFile && mv tempFile $1.satinput