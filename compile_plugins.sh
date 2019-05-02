#!/usr/bin/env bash

OUT="out"

rm -rf ${OUT}/plugins
mkdir ${OUT}/plugins

for pluginSrc in $(find plugins -name "*.cpp"); do
    echo "Compiling ${pluginSrc}"
    NAME=$(echo ${pluginSrc} | sed "s/.cpp//")
    g++ -fPIC -shared ${pluginSrc} -o ${OUT}/${NAME}.so
done

