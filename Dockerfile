# Używamy oficjalnego obrazu Ubuntu jako bazowego
FROM ubuntu:20.04

# Ustalamy zmienną środowiskową, aby uniknąć interakcji podczas instalacji pakietów
ENV DEBIAN_FRONTEND=noninteractive

# Aktualizujemy system i instalujemy wymagane pakiety
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    git \
    && rm -rf /var/lib/apt/lists/*

# Tworzymy katalog na nasz kod w kontenerze
WORKDIR /app

# Kopiujemy pliki z lokalnego systemu do kontenera (zmień ścieżki na odpowiednie)
COPY . .

# Budujemy nasz projekt (dostosuj komendę budowania w zależności od struktury projektu)
RUN rm -rf build && mkdir -p build && cd build && cmake .. && make

# Ustawiamy katalog roboczy na build
WORKDIR /app/build

# Określamy, co ma być uruchomione w kontenerze (np. nasz plik wykonywalny)
CMD ["./UniversityDatabase-app"]
