RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

make testGraph || exit
mkdir -p output

rm -f output/TestGraph.out
 
./testGraph > output/TestGraph.out

r=`diff -B output/TestGraph.out   output/TestGraph.exp `
if [[ "$r" == "" ]]; then
  echo -e "====== ${GREEN} Output Matches${NC} ======"
else
  echo -e "=========== ${RED} Output Mismatch${NC} ============"
  echo -e "       ${RED}(your output on left, expected on right)${NC}  "    
  diff -y -B output/TestGraph.out   output/TestGraph.exp
  
  echo -e " ${RED} Your output in:     ./output/TestGraph.out ${NC}"
  echo -e " ${RED} Expected output in: ./output/TestGraph.exp ${NC}"
  echo -e "=========== ${RED} End of Output Mismatch${NC} ============"
fi


  


