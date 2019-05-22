#!/usr/bin/env bash

# Main driver to build programs
# Author Xin Shi <shixin@ihep.ac.cn>
# Created [2016-03-28 Mon 08:19]


usage() {
    printf "NAME\n\tbuild.sh - Main driver to build programs\n"
    printf "\nSYNOPSIS\n"
    printf "\n\t%-5s\n" "./build.sh [OPTION]" 
    printf "\nOPTIONS\n" 
    printf "\n\t%-5s  %-40s\n"  "1"  "build Jpsi2invi analyzer" 
    printf "\n\t%-5s  %-40s\n"  "2"  "build Jpsi2incl analyzer"
    printf "\n\t%-5s  %-40s\n"  "3"  "build Jpsi2pnpi analyzer"
    printf "\n\t%-5s  %-40s\n"  "4"  "build Jpsi2lplm analyzer"
    printf "\n\t%-5s  %-40s\n"  "5"  "build Jpsi2geta analyzer"
    printf "\n\t%-5s  %-40s\n"  "6"  "build Mumu analyzer"
    printf "\n\n" 
}

if [[ $# -eq 0 ]]; then
    usage
    echo "Please enter your option: "
    read option
else
    option=$1    
fi


case $option in 
    1) echo "Building Jpsi2invi module..."
       cd Analysis/Physics/PsiPrime/Jpsi2invi/Jpsi2invi-00-00-01/cmt 
       gmake  
       ;;
    2) echo "Building Jpsi2incl module..."
       cd Analysis/Physics/PsiPrime/Jpsi2incl/Jpsi2incl-00-00-01/cmt 
       gmake  
       ;;
    3) echo "Building Jpsi2pnpi module..."
       cd Analysis/Physics/PsiPrime/Jpsi2pnpi/Jpsi2pnpi-00-00-01/cmt 
       gmake 
       ;; 
    4) echo "Building Jpsi2lplm module..."
       cd Analysis/Physics/PsiPrime/Jpsi2lplm/Jpsi2lplm-00-00-01/cmt
       gmake
       ;;
    5) echo "Building Jpsi2geta module..."
       cd Analysis/Physics/PsiPrime/Jpsi2geta/Jpsi2geta-00-00-01/cmt
       gmake
       ;;
    6) echo "Building Mumu module..."
       cd Analysis/Physics/PsiPrime/Mumu/Mumu-00-00-01/cmt
       gmake
       ;;


esac

