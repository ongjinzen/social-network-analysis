RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'
n=`ls graphs/*in | grep -o '[0-9][0-9]*' | sort | tail -n1`
make || exit
mkdir -p output
if [ $# -eq 1 ]; then
  i=$1
  ./testDijkstra graphs/$i.in > output/Dijkstra$i.out
  r=`diff dijkstraPaths/Dijkstra$i.out output/Dijkstra$i.out`
  if [[ "$r" == "" ]]; then
    echo -e "====== ${GREEN}[$i] Output Matches${NC} ======"
  else
    echo -e "=========== ${RED}[$i] Output Mismatch${NC} ============"
    diff dijkstraPaths/Dijkstra$i.out output/Dijkstra$i.out
  fi
  rm output/Dijkstra$i.out
  exit
fi
for i in `seq 1 $n`; do
    ./testDijkstra graphs/$i.in > output/Dijkstra$i.out
    r=`diff dijkstraPaths/Dijkstra$i.out output/Dijkstra$i.out`
    if [[ "$r" == "" ]]; then
      echo -e "====== ${GREEN}[$i] Output Matches${NC} ======"
    else
      echo -e "=========== ${RED}[$i] Output Mismatch${NC} ============"
      diff dijkstraPaths/Dijkstra$i.out output/Dijkstra$i.out
    fi
    rm output/Dijkstra$i.out
done
