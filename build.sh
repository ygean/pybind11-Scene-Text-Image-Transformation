rm MLSTransformer.so
# rm Augment.so
rm -rf build
mkdir build
cd build
cmake -D CUDA_USE_STATIC_CUDA_RUNTIME=OFF ..
make
cp MLSTransformer.so ../
# cp Augment.so ../

rm -rf build
