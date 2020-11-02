# C++ #
## 1. Podstawowe pojęcia ##

**Klasa** - wirtualny byt integrujący dane (atrybuty) i metody. Klasa sama w sobie nie stanowi obiektu - jest jedynie opisem właściwości i możliwych zachowań obiektu.

**Obiekt** - inaczej instancja klasy, stanowi konkretny egzemplarz bytu o właściwościch zdefiniowanych przez klasę.

**Abstrakcja** - rodzaj uogólnienia, mający na celu ukrycie nieistotnych szczegółów problemu w celu pokazania szerszego kontekstu

**Klasa konkretna** - Klasa, która ma zdefiniowane wszystkie atrybuty i operacje.

**Klasa abstrakcyjna** - Klasa, w której przynajmniej jedna metoda jest czysto wirtualna.

> ! Należy pamiętać o dodaniu wirtualnego destruktora w każdej klasie abstrakcyjnej. Jeśli mamy obiekt klasy konkretnej, ale rzutowany na typ abstrakcyjny, to przy niszczeniu obiektu wywolany zostanie konstruktor typu abstrakcyjnego, który poprzez vtable będzie wskazywał na konstruktor konkretnego typu pochodnego. Gdy nie dodamy wirtualnego konstruktora - nie zostanie wywołany tym samym konstruktor typu pochodnego, czyli faktycznie tego, który chcemy zniszczyć, bo nie będzie go zwyczajnie w vtable. W takiej sytuacji wywoła się jedynie konstruktor klasy abstrakcyjnej.

**Interfejs** - Zbió metod służący do komunikowania się jednostki oprogramowania ze światem zewnętrznym (klasami, komponentami, zbiorami klas itd...)

**Kontener** - Rodzaj klasy zawierającej kolekcję innych obiektów.

**Przeciążanie** - W C++ mamy możliwość nadpisania implementacji metod w podklasach. Możemy użyć sygnatury z nadklasy - wtedy w przypadku użycia obiektu klasy pochodnej implementacja metody zostanie zaczerpnięta z klasy pochodnej. Jeśli natomiast użyjemy obiektu klasy pochodnej, ale zrzutowanego na typ nadklasy, to aby użyć metody klasy pochodnej, musi być ona zadeklarowana w nadklasie jako wirtualna, aby znalazła się w vtable. Przeciążeać możemy też sygnatury - możemy utworzyć wiele metod o tych samych nazwach (lub funkcji), ale muszą różnić się co do typów / ilości argumentó i/lub typu zwracanego. Przy użyciu kompilator sam wydedukuje której metody użyć na podstawie podanych argumentów i typu zwracanego.

**Namespace** – przestrzeń nazw. Dzięki zadeklarowaniu metody w danej p-ni nazw, możemy deklarować obiekty o tych samych nazwach w innych p-niach nazw.

**Constexpr (C++11)** – oznaczamy tym funkcje, metody i dane ewaluowane (znane) na etapie kompilacji. Zmienne constexpr to takie dawne „definy” – ich wartość musi być zainicjalizowana w momencie tworzenia constexpr i nie może być zmieniona. Funkcje constexpr to funkcje, które rozwiązywane sa na etapie kompilacji, a ich efekt jest dopiero wkompilowywany (nie dzieją się w runtimie). 

**Predyktat** - funkcja zwracająca typ logiczny boolean

**Alias do typu** - w języku C++ możemy zdefiniować alias do typu, np:

    using A = int;

**Słowo kluczowe override** - dodane do deklaracji metody informuje kompilator, że spodziewamy się, że nadpisana zostanie metoda z nadklasy. Kompilator zgłosi błąd, jeśli metoda nadklasy nie będzie wirtualna.

**Słowo kluczowe final** - dodane do deklaracji metody informuje kompilator, że spodziewamy się, że nadpisana zostanie metoda z nadklasy i będzie to ostatnie przeciążenie w hierarchii. Kompilator zgłosi błąd, jeśli metoda nadklasy nie będzie wirtualna.
_______________________________________________________________

### Właściwości języów obiektowych ###

**Enkapsulacja** - Właściwość polegająca na izolowaniu dostępu do elementów programu (klas, metod, funkcji, danych), w celu wyeliminowania potencjalnych błędów wynikających z modyfikowania wyizolowanych elementów. W językach obiektowych enkapsulacja powinna być stosowana wszędzie tam, gdzie się da.

**Dziedziczenie** - mechanizm pozwalający klasom pochodnym przejmować zachowania i atrybuty z klas bazowych. Dzięki dziedziczeniu możliwe jest tworzenie rozszerzeń klas bazowych. 

> ! Przy dziedziczeniu w języku C++, konstruktor klasy pochodnej musi wywoływać konstruktor klasy bazowej. Jeżeli nie podamy jawnie konstruktora do wywołania - zrobi to za nas kompilator. Użyty zostanie konstruktor domyślny, zazwyczaj bezargumentowy.

**Polimorfizm** - inaczej wielopostaciowość. Właściowść polegająca na tym, że obiekt danje kalsy może występować zamiennie pod postacią (być typem) swojej klasy, ale także klas pochodnych i klasy bazowej. Polimorfizm pozwala oddzielić wyrażenia (konkretne instancje klas) od konkretnych typów. Dzięki polimorfizmowi, klient używający onkretnego obiektu nie musi znać jego wewnętrznej struktury. Co więcej, struktura ta może być podmieniana w zależności od potrzeb. Znany jest jedynie interfejs, który każdy z polimorficznych obiektów musi implementować.

________________________________

### Virtual Function Table ###

Jeśli napiszemy klasę z co najmniej jedną metodą wirtualną, zostanie ona uznana za typ polimorficny. Kompiator utworzy dla takiej klasy tzw. virtual function table (*vtable*). Jest to w rzeczywistości struktura zawierająca wskaźniki na implementacjie kolejnych metod oznaczonych jako wirtualne. Dalej, w momencie instancjonowania takiej klasy, kompilator utworzy dla każdej instancji, w pierwszych 4 bajtach tej klasy virtual pointer (vptr) - czyli wskaźnik wskazujący na vtable danego typu. Wywołanie wirtualnej metody jest berdziej skomplikowane niż zwykłej, gdzie skaczemy od razu do implementacji. W takim przypadku musimy wyłuskać wskaźnik vptr, dalej z vtbale wyłuskać wskaźnik na konkretną metodę i w ten sposób wskoczyć do implementacji. 

Gdy mamy podklasę, która dziedziczy z klasy wirtualnej, to dla podklasy również tworzony jest vtable ze wskaźnikami na implementację metod podklasy, jeśli są przeciążone, lub nadklasy, jeśli nie są przeciążone w podklasie. W takim wypadku wywołanie metody nieprzeciążonej na podklasie w efekcie wywołą tę samą metodę, co z nadklasy.

Jeżeli zrzutujemy obiekt podklasy na typ nadklasy, to vptr obiektu typu nadklasy przestawi się nam na vtable rzutowanej podklasy. W ten sposób będziemy mieli dostęp do implementacji podklasy, ale poprzez interfejs nadklasy - czyli uzyskujemy polimorfizm. Warto pamiętać, że w tej sytuacji możemy dobrać się jedynie do metod wirtualnych.

**Diamond problem** - Występuje gdy mamy strukturę dziedziczenia:

   A    
  / \    
 B   C         
  \ /    
   D    

Wtedy klasa D dziedziczy 2 razy niewirtualną implementację z klasy A. Ponieważ mamy "wklejone" dwa razy to samo, nie wiadomo która implementacja jest poprawna. Rozwiązaniem diamond problemu może być *dziedziczenie wirtualne*.

> Nie można dynamic castować na obiekt (trzeba na pointer)

> Jeśli zcastujemy – to tylko metody wirtualne będą miały implementację z typu który był kastowany(bo tylko one były w vtable). Zwykłe, niewirtualne metody, będą miały implementację z typu, na który rzutujemy!!

> ! Jeśli z kolei w klasie bazowej zrobimy metodę, której nie przeciążymy  klasie pochodnej i która nie będzie wirtualna, to w pochodnej klasie, poprzez dziedziczenie dostaniemy kopię implementacji, a przy dziedziczeniu wirtualnym – kopia implementacji będzie siedziała gdzieś obok, a my podziedziczymy tylko wskaźnik do całej implementacji.

> ! deta – jeśli mamy dziedziczenie tylko z 1 klasy – no to mamy vrt w pierwszych 4 bajtach. To znaczy, że jeśli sobie zrzutujemy – przestawimy ten vptr i odpalenie metody przez wyłuskanie vptr będzie proste, bo wiadomo, gdzie szukać tego vptr. Jeśli natomiast mamy dziedziczneie np. z 2 klas – no to mamy 2 vptr od 2 klas bazowych i siłą rzeczy jeden z nich będzie niżej o 4 bajty niż powinien. Ten dystans – to delta. Delta jest zapisywana razem z vptr, czyli tak naprawdę przy wielodziedziczneiu kompilator wygeneruje dłuższą klasę (4bajty – 1 vptr, 4 bajty 2 vptr i jeszcze int na delte).

**Dziedziczenie wirualne** – dodajemy słowo kluczowe virtual po ":" przy dziedziczeniu. Dziedziczenie wirtualne powoduje, że wewnątrz odziedziczonej klasy implementuje się obiekt klasy – dziadka (A – patrz przykład powyżej z diamond problem), ale jego delta jest nieistotna. Zamiast tego wewnątrz tej klasy dodaje się wskaźnik na tę implementację (całą, nie tylko elementy wirtualne!) – i tak dostęp do podziedziczonych metod uzyskuje się przez wyłuskanie wskaźnika. W klasie D zamiast odziedziczyć 2 implementacje – odziedziczymy tylko 2 wskaźniki, wskazujące na odziedziczoną implementację klasy A. Wirtualne dziedziczenie uniemożliwia stosowanie static_castów – trzeba używać dynamic castów.

______________________

## Konstruktory ##

**Konstruktor** - Specjalna metoda klasy C++, która jest wywoływana zawsze przy tworzeniu obiektu, nic nie zwraca, może przyjmować argumenty i ma nazwę taką samą jak nazwa klasy. Służy do zainicjowania obiektu początkowymi wartościami. Konstruktor, jak wszystkie metody, można przeciążać.

**Destruktor** - Specjakna metoda wywoływana podczas niszczenia klasy. Służy do deinicjalizacji pól klasy, zwalniania zasobów (patrz idion RAII).

### Rodzaje konstruktorów ###

**1. Konstruktor domyślny** - dodawany automatycznie w momencie tworzenia klasy C++. Nie ma argumentów i nie wykonuje żadnych zadań (sygnatura A()).

**2. Konstruktor zero argumentowy** - konstruktor, który nie posiada argumentów, lub jego argumenty mają przypisane wartości domyślne (np. A(int a = 1)). 

> ! Gdy argument ma przypisane wartości domyślne, wtedy można, ale nie trzeba ich podawać. W przypadku konstruktora z takimi argumentami, ponieważ nie ma konieczności ich podawania, będzie on traktowany jako zeroargumentowy

**3. Konstruktor wieloargumentowy** - konstruktor z listą argumentów, zdefiniownay jawnie

**4. Konstruktor kopiujący** - konstruktor służący do kopiowania zawartości obiektu do drugiego obiektu. Jako argument przyjmuje referencję do obiektu, z któego kopiujemy wartości atrybutów. Zdefiniowany jest domyślny konstruktor kopiujący, który kopiuje całą zawartość klasy.

	classConstrA(classConstrA& oClass) : _param1(oClass._param1)
	{
		std::cout << "User defined copy constructor called !" << std::endl;
		_param2 = new int;
		(*_param2) = *(oClass._param2);
	}	//Copy constructor

**5. Konstruktor przenoszący** - konstruktor służący do przenoszenia zawartości obiektu podanego jako argumenr przez referencję do r-wartości na obiekt, na którym wywołano konstruktor. (od C++11)

	classConstrA(classConstrA&& oClass) :
		_param1(oClass._param1), _param2(oClass._param2)
	//"Copy" parameters : do not have to move content pointed by vector - becouse we move, no aliasing of pointers will occur
	{
		std::cout << "User defined move constructor called !" << std::endl;
		oClass._param1 = 0;		  //Free param1 element
		oClass._param2 = nullptr; //Free param2 element
	}

**explicit** (C++11) – słowo kluczowe uniemożliwiające domyślną konwersję typów (implicite conversion) z użyciem konstruktorów i implicite copy initialization.

*Przykład (in class declaration):  explicit A(){}*

**Implicit conversion** – zachodzi wtedy, gdy funkcja nie przyjmuje danej podanego typu, ale przyjmuje inny typ, który może być poddany niejawnej konwersji do pożądanego typu. Wtedy kompilator sam przekonwertuje zmienną.

*Przykład:   A oA = 1  -> Wywoła oA(1)*

**Kopiujący operator przypisania** – operator przypisania wywoływany w momencie przypisania obiektu do obiektu. W takim wypadku operator przypisania zwraca wskaźnik na samego siebie do obiektu, który przyjmuje go do swojego konstruktora. Konstruktor kopiujący tworzonego obiektu wywoła się automatycznie. Operator przypisania jest wywoływany, gdy już stworzony obiekt jest przypisywany do innego obiektu. 

*Przykład: A& operator=(A& oA)*

	classConstrA& operator=(classConstrA& oClass)
	{
		std::cout << "User defined copy assignment operator called !" << std::endl;
		_param1 = oClass._param1;
		delete _param2;					//Delete old data
		_param2 = new int;				//Allocate place for new data
		*_param2 = *(oClass._param2);	//Copy data
		return *this;
	}

**Przenoszący operator przypisania** – operator przypisania wywoływany w momencie przenoszenia obiektu do obiektu. W takim wypadku operator przypisania zwraca wskaźnik na samego siebie do obiektu, który przyjmuje go do swojego konstruktora. Konstruktor przenoszący tworzonego obiektu wywoła się automatycznie.

*Przykład: A& operator=(A&& oA)*

	classConstrA& operator=(classConstrA&& oClass)
	{
		std::cout << "User defined move assignment operator called !" << std::endl;
		_param1 = oClass._param1;
		_param2 = oClass._param2;

		oClass._param1 = 0;			//Free content of old class
		oClass._param2 = nullptr;
	}

**Kasowanie domyślnego operatora (konstruktora)**  (C++11) – od C++11 możliwe jest jawne skasowanie wybranej domyślnej metody klasy – wtedy metoda ta nie będzie dostępna, np. można w ten sposób skasować operator New żeby uniemożliwić dynamiczną alokację pamięci, lub konstruktor kopiujący. *Syntax: A(const A&) = delete;* - kasowanie domyślnego konstruktora kopiującego

**Zaznaczenie domyślnego konstruktora** (C++11) – od C++11 możliwe jest jawne wyartykułowanie chęci użycia domyślnego konstruktora, wystarczy wypisać *syntax: A() = default;* Wtedy przeciążenie konstruktora własnym będzie niemożliwe, bo kompilator ma jawnie powiedziane, że ma użyć konstruktora domyślnego.

**KIEDY UŻYWAĆ KONSTRUKTORÓW KOPIUJĄCYCH I PRZENOSZĄCYCH ZDEFINIOWANYCH PRZEZ UŻYTKOWNIKA** - Gdy klasa ma tylko atrybuty, możemy skorzystać z domyślnych konstruktorów, jednak gdy klasa ma wskaźnik, to skorzystanie z domyślnego konstruktora skopiuje wskaźnik - ale nie obszar pamięci na który wskaxuje. W efekcie skopiowany obiekt będzie miał wskaźnik do tego samego obszaru pamięci, co stary - nastąpi aliasing wskaźników. W takiej sytuacji dealokacja wskazywanego zasobu dotknie wszystkich kopii - a więc, dla bezpieczaństwa, w tych przypadkach zalecane jest użycie własnych konstruktorów.

### Reguły użycia konstruktorów ###

**Reguła 3** - dot. starszych wersji C++. Mówi, że jeśli zdefiniowano destruktor, należy jawnie zdefiniować konstruktor kopiujący i kopiujący operator przypisania (aby uniknąć problemów z kopiowaniem klas ze wskaźnikami)

**Regułą 5** - dot. nowszych wersji (od C++11). Mówi, że jeśli zdefiniowano destruktor, należy jawnie zdefiniować konstruktory przenoszący i kopiujący, oraz ich operatory przypisania.

**Reguła 0** - Mówi, że powinniśmy tak pisać kod, aby wykorzystać domyślne konstruktory i operatory przypisania - nie definiować własnych konstruktorów ani destruktorów.

### L-value i R-value ###

**L-wartość**– wszystko co może stać po lewej stronie znaku =. Inaczej mówiąc – wszystkie obiekty istniejące dłużej niż przez 1 wyrażenie.

**R – wartość**– wszystko co może stać po prawej stronie znaku =. Inaczej mówiąc – wszystkie obiekty istniejące przez jedno wyrażenie.

**Referencja** – alias do obiektu. Referencja jest w rzeczywistości czymś pomiędzy wskaźnikiem a obiektem. Do referencji przypisujemy adres obiektu, ale można to zrobić tylko raz. Referencji (adresu) nie można też przestawić, a używanie referencji nie powoduje alokowania wskaźnika (adresu). Po utworzeniu referencji możemy z niej korzystać tak jak z oryginalnego obiektu. Referencja może być przypisana do zmiennej z jednym wyjątkiem – stałą referencją do typu. Polega to na tym, że w miejsce referencji możemy podać stałą wartość oczekiwanego typu, mimo, że jest to r-value (np. możemy przekazać jako argument liczbę 5 w miejsce int&, a nie musimy tworzyć najpierw zmiennej int, potem przekazywać referencję do niej).

**Referencja do r – wartości** (C++11) –alias do obiektu, który jeszcze nie ma nazwy. Możemy w ten sposób np. stworzyć alias do obiektu, który jeszcze nie został zainicjalizowany. Stworzny na potrzeby semantyki przenoszenia.

**Semantyka przenoszenia** – w klasycznym podejściu, aby przenieść obiekt, program musiałby utworzyć nową instancję, skopiować do niej dane, a następnie usunąć starą. Od c++11 semantyka przeniesienia uległa zmianie, i teraz możemy po prostu „uznać” nową instancję za starą. Dane w pamięci nie muszą być kopiowane, po prostu po przeniesieniu odnoszą się one do nowego obiektu. 

**Std::move \<utility>** - funkcja działa jak rzutowanie. Jest to bezwarunkowe rzutowanie podanego argumentu na referencję do r-wartości i zwrócenie jej jako argument.

___

## Kwalifikatory dostępu ##

**Public** - wszsytko jest jawne, dostępne na zewnątrz klasy

**Protected** - klasy pochodne dziedziczą obiekty protected, a na zewnątrz obiekty te nie są dostępne

**Private** - Obiekty są zakapsułkowane do użytku tylko wewnątrz klasy

Dziedziczenie:
1)	Bez kwantyfikatora -> private
2)	Z private: private->not accesed, protected->private, public->private
3)	Z protected: private->not accesed, protected->protected, public->protected
4)	Z public: private->not accesed, protected->protected, public->public

______

## Obsługa błędów ##

1)	**Asercja** – program zostaje przerwany w wyniku asercji. Najmocniejsza metoda kontroli, nie może być stosowana do raportowania funkcji nadrzędnej poprawności wykonywania zadania. (istnieje static_assert – asercje constexpr, na etapie kompilacji)

2)	**Zwracanie kodu błędu** – można zwracać informacje czy funkcja wykonała zadanie poprawnie. Metoda niezalecana, bo błędy te muszą być sprawdzane i obsługiwane po wyjściu z funkcji, w miejscu wywołania, a to miesza nieco konteksty i ogranicza czytelność. Co więcej – taka funkcja nie może zwracać niczego innego.

3)	**Wyjątki (C++)** – metody mogą rzucać wyjątkami (chyba że są zadeklarowane jako noeecept, wtedy, nawet jeśli rzuci wyjątkiem, nie zostanie on obsłużony), a wyjątki mogą być łatabe i obsługiwane na zewnątrz wywołania funkcji, w blokach try{   wywołanie funkcji} Catach(wyjarek1)… Catach(…) – dowolny inny wyjątek.

_____

## Rzutowanie ##

1)	**Niejwane (domyślne)** – nie podajemy jawnie operatora rzutowania, a kompilator sam domyśla się w jaki sposób zrzutować dane

2)	**W stylu C**– rzutować możemy wszystko na wszystko, ale rzutowanie polega na poinformowaniu kompilatora, że od tej pory dana typu A ma być traktowana jak dana typu B. Nie dochodzi do żadnej konwersji danej żeby pasowała do nowego typu.

> !Rzutowanie w stylu C++ jest preferowane ze względu na jasną intencję autora co do typu rzutowania (te w stylu c++ są dłuższe i łatwiejsze do znalezienia), oraz, rzutowania w stylu c++ są przetwarzane przez kompilator, a te w stylu c już nie.

3)	**Static_cast** – służy do rzutowania typów, najczęściej stosowany operator rzutowania. Jego działanie dla większości typów zasadniczo nie różni się od rzutowania w stylu C. W praktyce powoduje ten sam efekt co niejawna konwersja między typami. Jeśli niejawna konwersja jest zdefiniowana, możemy użyć static cast. Static cast nie zadziała jednak dla konwersji wskaźników lub referencji z const i volatile. Za pomocą static cast możemy śmiało konwertować wskaźniki i referencje „typowych” typów. Może być używany do dodania consta (ale nie do usunięcia). Static cast zapewnia ochronę przed rzutowaniem na typy, które do siebie nie pasują (np. chara do wskaźnika na inta, lub typu wskaźnikowego na typ bazowy).

4)	**Const_cast** – rzutowanie typów z kwantyfikatorem const lub voltaile. Za pomocą const_cast można rzutować wyłącznie wskaźniki lub referencje, które różnią się od siebie kwantyfikatorem const lub volatile. Możemy np. zrzutować constowy wskaźnik lub referencję do niekonstowego obiektu na niekonstowy wskaźnik lub referencję. W praktyce powinniśmy unikać const_casta – jeżeli ktoś zakonstował jakiś wskaźnik lub referencję, to zrobił to intencjonalnie i nie powinniśmy naruszać tego ograniczenia.

5)	**Dynamic_cast** – służy do rzutowania typów polimorficznych w górę, w dół i w poprzek hierarchi dziedziczenia. Podobnie jak const_cast służy do rzutowania referencji i wskaźników. Jeżeli rzutowanie się powiedzie, dynamic_cast zwraca wskaźnik do zrzutowanego obiektu, jeśli nie – zwraca nullptr. W górę hierarchii możemy rzutować niejawnie, za pomocą static casta, za pomocą rzutowania z C (nie zalecane – działa tylko jak mamy pojedyncze dziedziczenie – delta), lub za pomocą dynamic casta. W dół hierarchii – działa również static_cast, ale w bok – tylko dynamic cast.

6)	**Reinterpret_cast** – służy do bezpośredniego rzutowania typu na typ. Używany rzadko, z rozwagą, bo nie zapewnie ochrony przed niepoprawnym rzutowaniem. Zazwyczaj służy do rzutowania – reinterpretacji ciągów bitowych. Jest podobny funkcjonalnością do rzutowania w stylu c.

____

## Dynamiczna alokacja pamięci ##

W C++ możemy alokować pamięć dynamicznie tak samo jak w C. Istnieją też takie same rodzaje alokacji jak w C. Dodatkowo C++ udostępnia 2 nowe operatory – New do alokowania, a delete do zwalniania pamięci. Warto przyjrzeć się inteligentnym wskaźnikom (make_unique) aby nie alokować pamięci wprost.

____

## Inteligentne wskaźniki ##

\<memory>

Użycie inteligentnych wskaźników ma sens gdy korzystamy z dynamicznej alokacji pamięci. Gdy alokujemy pamięć, otrzymujemy wskaźnik na zaalokowaną jednostkę pamięci. Wskaźnik określonego typu. Zwyczajny wskaźnik pozwala na dostęp do zaalokowanej pamięci, pozwala się również skopiować. Co więcej, w przypadku, gdy nie ma potrzeby używania dłużej zaalokowanej pamięci, pamięć należy zwolnić (korzystając zresztą z otrzymanego wskaźnika). Czasami takich ścieżek, które prowadzą do bezużyteczności zaalokowanej pamięci jest wiele – wtedy należałoby w każdej pamiętać o zwolnieniu zasobów, bo inaczej narażamy się na wycieki pamięci. 

Nieco pomocne może okazać się użycie inteligentnych wskaźników. Inteligentne wskaźniki kontrolują liczbę instancji wskaźników do obiektu, kontrolują również czas życia obiektu – gdy wskaźnik (lub wszystkie) zostanie zniszczony – zwalniana jest również pamięć na jakie wskazuje wskaźnik. Rozróżniamy 3 typy inteligentnych wskaźników:

1)	**Unique_ptr** – dostęp do obiektu może odbywać się tylko poprzez jedną instancję takiego wskaźnika. Wskaźnika nie można kopiować, a jego zniszczenie jest jednoznaczne ze zniszczeniem obiektu. Tworzenie: poprzez operator New lub poprzez std::make_unique<>()

2)	**Shared_ptr** – wskaźnik można kopiować, a sam wskaźnik ma liczbę instancji (licznik). Gdy liczba kopii się wyzeruje (wszystkie shared pointery zostaną zniszczone) – wtedy niszczony jest też sam obiekt. Tworzenie: poprzez operator New lub poprzez std::make_shared<>()

3)	**Weak_ptr** – wskaźnik, który trzyma „nie dostępową” referencję do obiektu. Nie można za jego pomocą dostać się do obiektu (trzeba go przekształcić w shared_ptr metodą .lock()), służy bardziej do trzymania referencji i do łamania cykli referencyjnych. Za pomocą weak_ptr możemy się dowiedzieć, czy obiekt referencyjny nadal istnieje. Weak pointer jest podporządkowany do zasobu trzymanego przez inny wskaźnik. 

**Cykl referencji** – pojawia się, gdy obiekty zawierają wskaźniki wskazujące na siebie nawzajem (np. lista wskazująca na poprzedni i następny obiekt).  Wtedy, nie da się usunąć elementu, bo shared_ptr do obiektu następnego jest również shared_ptr do poprzednika obiektu za nim – licznik referencji będzie równy 2. Gdy chcemy usunąć element ze środka – shared_ptr poprzednika nie pozwoli na zniszczenie zasobu (bo jego licznik referencji będzie równy 1) mini, że chcemy zniszczyć shared_ptr następnika. 

___

## Templaty ##

**Template** - element języka umożliwiający programowanie uogólnione, to znaczy bez wcześniejszej znajomości konkretnych typów danych. Szablon rozwiązywany jest na etapie kompilacji, a konkretyzowany w momencie użycia zatemplatowanego obiektu.

**Szablon klasy (typu)** – umożliwia zdefiniowanie nieznanego typu i używanie go w klasie (funkcji). Typ podaje się w momencie tworzenia instancji klasy. Co ważne, dla każdego podanego do instancji typu zostanie wygenerowany inny egzemplarz klasy.

**Szablon wartości** - umożliwia zdefiniownie wartości określonego typu i używanie go w klasie (funkcji). Wartość podaje się w momencie użycia elementu.

    //Function template
    template <typename T, int N> T increment(T argument)
    {
        return N*(++argument);
    }

    //Class template
    template <typename T>
    class Klasa
    {
    public:
        Klasa(T a): _a(a) {}
        T decrement(T value);

        T _a;
    };

! szablony można zagnieżdżać

! szablon może mieć dowolnie dużo odwołań

! Szablon może dotyczyć klasy lub funkcji

! Szablon może służyć do rekurencyjnego, funkcyjnego programowania – wymaga szablonu z rekuencją i szablonu tzw. specjalizacji – kończącego rekurencję

**Szablon wariadyczny** - umożliwia przekazanie nieznanej ilości typów (dowolnej ilości).

    template <typename Head, typename ...Tail>
    void variadicTemplate (Head head, Tail... a)
    {
        cout << "Variadic template test: \n";
        cout << head << "  ";
        (print(a), ...);
        cout << endl;
    }

Znak "..." zostanie rozwinięty we wszystkie rpzekazane typy (wartości). Np *foo(Tail...)* wykona metodę foo na każdej wartośi przekazanej przez tamplate.
___

**Funktor** – klasa która posiada przeciążony operator (). Dzięki temu możemy używać jej jak zwykłą funkcję, ale posiada atrybuty klasy (może mieć stan np.) . Funktor jednoargumentowy nazywamy generatorem, dwuargumentowy - funkcją dwuargumentową, trzyargumentowy - funkcją trzyargumentową itd...

**Funkcja lambda** – funkcja która nie posiada nazwy, która, której implementacja znajduje się w miejscu wywołania. Notacja lambda zawiera miejsce przechwytywania (gdzie wpisujemy wszystkie dane widoczne wewnątrz funkcji), listę argumentów i ciało mają składnie jak przy normalnej funkcji: *\[przechwywytywanie](args){impl;}*
