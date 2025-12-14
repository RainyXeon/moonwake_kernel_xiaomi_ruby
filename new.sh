echo "Remove Official Local Version String"
rm "localversion-moon"
echo "Add experimental version string"
echo "-DeepMoonX" > localversion-00-experimental
echo "Add commit version string"
echo "-$(git rev-parse --short=7 HEAD)" > localversion-01-experimental
echo "Add run number string"
echo "-$(date '+%Y%m%d-%H%M')" > localversion-02-experimental
echo "Check kernelsu intergration, preview:"
cat drivers/Makefile | grep "CONFIG_KSU"
cat drivers/Kconfig | grep "CONFIG_KSU"
cat out/.config | grep "CONFIG_KSU"
echo "Add new banner, preview:"
new_banner_data=$(cat <<'EOF'
======================================================
     *          *       *      *        *     *   
  *        *          *     *      *         *    
      *     *     *        *   *       *     *    
 *        *     *        *        *         *     
    *        *      *        *        *         * 
======================================================
 - DeepMoonX Kernel [PRIVATE]
 - By RainyXeon
======================================================
EOF
)
echo "$new_banner_data"
cd ./AnyKernel3
echo "$new_banner_data" > banner
echo "Done!"