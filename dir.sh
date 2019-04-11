#!bin/bash
dirold3=JetID3
dirold=JetID
dirnew=AK4mjjdeta

sed -i "s;$dirold3;$dirnew;" config/*.xml
sed -i "s;$dirold;$dirnew;" config/*.xml