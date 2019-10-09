RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

if [ $# -eq 1 ]; then

  make testLanceWilliamsHAC || exit
  mkdir -p output

  i=$1
  
  case  $i in
    1|2|3|4|5)  
      rm -f  output/LW$i.out
      ./testLanceWilliamsHAC graphs/$i.in |sort -n  > output/LW$i.out
      r=`diff -B output/LW$i.out   output/LW$i.exp `
      if [[ "$r" == "" ]]; then
        echo -e "====== ${GREEN}[$i] Output Matches${NC} ======"
      else
        echo -e "=========== ${RED}[$i] Output Mismatch${NC} ============"
        echo -e "       ${RED}(your output on left, expected on right)${NC}  "      
        diff -y -B  output/LW$i.out   output/LW$i.exp 
        echo -e " ${RED} Your output in:     ./output/LW$i.out ${NC}"
        echo -e " ${RED} Expected output in: ./output/LW$i.exp ${NC}"         
        
      fi
      ;;
    *)
        echo " Usage: ./testLW.sh [1|2|3|4|5]  "
        ;;
   esac
   
else
  echo " Usage: ./testLW.sh [1|2|3|4|5]  "
fi

