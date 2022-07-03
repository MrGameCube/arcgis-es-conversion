# arcgis-es-conversion
Utilties which were developed for the migartion to esri ES Modules in a large codebase using the legacy esri Loader.
## Usage
The program needs the extracted npm package to function: https://www.npmjs.com/package/@arcgis/core
The command:`npm view @arcgis/core@<VERSION>` can be used to get the tarball download URL.

### Extraction
The  extraction step outputs a file which maps class names (e.g FeatureLayer, FeatureSet, Map, MapView...) to a ES-Module import path (@arcgis/layers/FeatureLayer, ...).
It uses the format `<CLASS NAME>#<IMPORT PATH>`

### Conversion
The conversion step is meant to convert the used class names in a code base and add the necessary imports to each file.
The code is not yet complete.

## Warning
This code was written pruely as a practise exercise and should not be considered fail-proof or complete.

