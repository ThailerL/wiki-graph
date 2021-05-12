# Wiki-graph

## tslietz2-sohamk2-ttz2

Description

## Getting Started

### Compiled with

- clang 6.0.1
- Boost 1.53
- Qt 4.8.7

### Setting Up

1. Clone this repo and go to its directory.
   ```
   git clone https://github-dev.cs.illinois.edu/cs225-sp21/tslietz2-sohamk2-ttz2.git
   cd tslietz2-sohamk2-ttz2/
   ```
2. In a new directory, download the graph and name data from [Stanford's SNAP dataset of English Wikipedia in 2013](https://snap.stanford.edu/data/enwiki-2013.html) and extract them. Return to the main directory.
    ```
    mkdir data
    cd data/
    wget https://snap.stanford.edu/data/enwiki-2013.txt.gz 
    wget https://snap.stanford.edu/data/enwiki-2013-names.csv.gz
    gunzip *
    cd ../
    ```
3. Make the prep-data executable and use it to trim the data to include nodes of interest, while keeping the size reasonable.
    ```
    make prep-data
    ./prep-data 1000 5000 data/enwiki-2013.txt data/trimmed.txt
    ```