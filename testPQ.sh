RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

make testPQ || exit
mkdir -p output

rm -f output/TestGraph.out
 
./testPQ > output/TestPQ.out

r=`diff -B output/TestPQ.out   output/TestPQ.exp`
if [[ "$r" == "" ]]; then
  echo -e "====== ${GREEN} Output Matches${NC} ======"
else
  echo -e "=========== ${RED} Output Mismatch${NC} ============"
  echo -e "       ${RED}(your output on left, expected on right)${NC}  "
  diff -y -B output/TestPQ.out   output/TestPQ.exp
  echo -e " ${RED} Your output in:     ./output/TestPQ.out ${NC}"
  echo -e " ${RED} Expected output in: ./output/TestPQ.exp ${NC}"
  echo -e "=========== ${RED} End of Output Mismatch${NC} ============"
fi


  


