# DESCRIPTION

## Estetyka

* Używamy saasów aby nie musieć walczyć z estetyką
* poukładane repo, easy to use dla usera/klienta
* instrukcja jak to wdrożyć

## Co zrobiliśmy podczas hackathonu

### Co mieliśmy wcześniej

* Gotowy hardware (bez czujników)
* Kilka testowych node z GPS (przerobiliśmy je z GPS na temperatura + światło)
* jeden prosty projekt oparty o grafanę
* aplikację frontendową prezentującą dane w postaci wykresów (nie użyliśmy jej na hackathonie, zamiast tego mamy grafanę)
* aplikację przetwarzającą http requesty w zapytania sql (nie użyliśmy, zamiast tego napisaliśmy nową w pythonie)
* Działający TTN Gateway


### Co zrobiśmy podczas hackthonu

* Aplikację w Pythonie odbierającą dane z brokera MQTT i zapisująca pakiety do bazy danych MySQL
* Pozstawiliśmy bazę danych MySQL na db4free.net i zaprojektowaliśmy nowe tabele
* Stronę Github Pages jako dokumentację
* Ponownie uruchomiliśmy TTN Gateway oraz testowe TTN Node własnej produkcji
* Nowy projekt na grafanie
* Ogarnęliśmy WorldMap plugin na Grafanie
* Fancy gif

## Przydatność biznesowa

* dbamy o łodzian, a wszyscy chcą żyć w czystym mieście
* zwracamy uwagę na problemy w mieście, czas abyśmy wszyscy zadbali o nasze miasto
* sprawdźmy które parki są najcichsze i najspokojniejsze
* projekt open source, każdy elektornik-hobbysta może się przyłaczyc do projektu

## Sposób wykonania od strony technicznej

* Node (zasilanie + Arduino + sensors + radio module RFM95)
* Gateway
* TTN Cloud
* Python script (mqtt)=>(MySQL)
* MySQL
* Grafana

* Github
* Github Pages

### Użyte technologie
* MySQL
* Python
* Git, Github.com
* Arduino
* TheThingsNetwork
*   TTN Stack
*   TTN Python SDK
* Grafana

* JSON

### Hardware
* Arduino
* RFM95W
* sensors:

## Aktualny stan projektu
### Już działające
1. Landing page
2. Python script
3. Projekt Arduino
4. Projekt hardware (gotowy shield ttn-tul-node-v1)
5. Baza danych
6. Grafana

### Gotowe do wdrożenia
1. uruchomić skrypt pythona na serwerze produkcyjnym
2. Opublikować dashboard Grafany online
3. Automatyzajca przekazywania danych dla nowych użytkowników

## Monetyzacja
* Donejty
* SPrzedaż open source hardware

## Przyszłość
* Wdrażamy na serwerach PŁ
