# PA-tema1

## Descriere Implementare

### Problema 1 - Servere

-   double find_system_power(double current_choice, vector<int> power, vector<int> capacity)

    > Functia asta calculeaza puterea de calcul a sistemului dat pentru o singura valoare de curent de alimentare.

    > Returneaza minimul dintre puterile de calcul ale serverelor, calculate ca in exemplu.

-   double find_best(double lo, double hi, double old_result, vector<int> power, vector<int> capacity)

    > Gaseste maximul puterii de calcul totale, adica al functiei find_system_power (notata in continuare cu f), in intervalul [lo, hi] folosind un algoritm de tipul divide et impera.

    > La fiecare pas este calculat f(lo) si f(hi). Daca f(lo) < f(hi), Apelam recursiv functia pentru subintervalul stang [lo, mid]. Altfel o apelam pentru cel drept [mid, hi]. Forma functiei f date garanteaza ca in timp ne vom apropia de maximul global al functiei.

    > Conditia de oprire: La fiecare pas calculam valoarea functiei in mijlocul intervalului (f(mid) - mid_power) si retin valoarea functie in mijloc la pasul trecut (old_power). Diferenta in modul a acestor doua este o aproximare a derivatei functiei f'(mid). Daca aceasta scade sub o toleranta data, ne-am apropiat suficient de mult de maximul functiei si returnam rezultatul final (panta functiei a devenit lina). Am considerat o toleranta/eroare de 0.001, deoarece valoarea finala trebuie sa aiba o precizie de o zecimala.

-   int main()

    > Citesc nr de servere, puterea de calcul si capacitatea fiecarui server.

    > Consider ca marginea inferioara a intervalului de cautare este minimul dintre pragurile de alimentare ale serverelor, si marginea superioara este maximul. Se observa ca valoarea curentului de alimentare pentru care puterea de calcul sa fie maxima sigur nu va fi in afara acestui interval.

    > Afisez valoarea maxima a puterii de calcul, gasita de find_best.

### Complexitate temporala

    Este dominata de find_best.

    T(n) = (3 * O(n) + O(1)) * O(log(n)) = O(n * log(n))

---

### Problema 2 - Colorare

-   unsigned long long log_power(unsigned int base, unsigned int exp)

    > Foloseste algoritmul prezentat la laboratorul de divide et impera pentru exponentiere in timp O(log(n)), calculand la fiecare pas restul impartirii la MOD, unde MOD = 1'000'000'007.

-   unsigned int get_nr_combinations(const vector<Group>& groups)

    > Folosesc un algoritm de tip greedy pentru a calcula numbarul de combinari posibile de patratele.

    > Am 2 cazuri de baza in functie de tipul primei zone din tablou: V sau H.

    > Am 4 cazuri generale pentru a stii cu cat trebuie inmultit nr vechi de combinari in functie de tipul ultime zone calculate si de tipul zonei curente (V, V), (V, H), (H, V), (H, H).

    > Pentru a optimiza timpul de executie, fac inmultirea de la cazul general doar cand am tranzitii intre grupuri de zone, in schimb voi apela functia log_power.

-   int main()

    > Citesc nr de grupuri din fisierul de intrare, si retin informatiile despre nr de zone din fiecare grup si tipul lor intr-un struct Group.

    > Apelez get_nr_combinations pentru a gasi nr de combinari pentru zonele din tablou, modulo MOD.

    > Scriu rezultatul in fisierul de output.

### Complexitate temporala

    Este dominata de get_nr_combinations.

    T(n) = O(n * log(k))
    n - nr de grupuri de zone
    k - nr de inmultiri facute in medie pentru o zona

---

### Problema 3 - Compresie

-   unsigned int compress_arrays(unsigned int A[], unsigned int n, unsigned int B[], unsigned int m)

    > Folosesc un algoritm greedy pentru a gasi lungimea finala a sirului comprimat.

    > Incep prin a considera primul subsir din fiecare sir ca fiind primul element. Retin indexul elementului final - 1 si suma totala a subsirului.

    > Cat timp mai am elemente din siruri care nu au fost bagate in ultimul subsir:

        - Daca suma subsirului a e mai mica decat cea a subsirului b, pun urmatorul element din A in subsirul a, adica incrementez indexul de final al subsirului si adun valoare elementului din A la suma subsirului.

        - Daca suma subsirului b e mai mica decat cea a subsirului a, pun urmatorul element din B in subsirul b, analog.

        - Eventual voi avea 2 subsiruri cu aceeasi suma. In acest caz pot indica ca au fost "comprimate" intr-un singur element reprezentand suma lor prin incrementarea lui length_seen_array (retine nr de astfel de sume). Voi incepe un subsir nou pentru fiecare sir prin incrementarea contorului si actualizarea sumelor cu valoarea primului element din noul subsir.

        - La final returnez length_seen_array, care va fi numarul de perechi de subsiruri care au avut lungimea egala.

-   int main()

    > Citesc lungimile sirurilor si elementele din ele din fisierul de input.

    > Daca suma elementelor din siruri difera, nu voi putea sa le comprim, deci scriu -1. Alftel, apelez compress_arrays pentru a gasi lungimea maxima a sirului "comprimat".

    > Scriu rezultatul lui compress_arrays in fisierul de output.

### Complexitate temporala

    Este dominata de compress_arrays.

    T(n,m) = O(n + m)
    n - lungimea sirului 1
    m - lungimea sirului 2

---

### Problema 4 - Criptat

-   unordered_map<char, int> countLetters(const vector<string>& strings)

    > Returneaza un hashmap ce are drept chei numarul unic de litere din parola (maxim 8) si ca valori frecventa lor in parola. Parametrul primit este un vector cu toate cuvintele ce reprezinta initial parola.

-   int find_letter_frequency(const char my_ch, const string& str)

    > Functie auxiliara pentru gasirea frecventei unei litere intr-un string.

-   int get_password_length(vector<string> words, int password_length, const char letter, int frequency)

    > Acest algoritm este unul de tip greedy care nu gaseste solutia corecta pentru problema pentru orice caz dat. Cu o euristica mai buna (comparator pentru sort) ar putea trece mai multe teste. O solutie optima ar folosi programare dinamica.

    > Trebuie sa scot cuvinte din parola pana cand litera primita ca parametru devine dominanta. Parola nu este retinuta intr-un string, ci ca o lista de cuvinte, alaturi de alti parametrii importanti (lungimea parolei si frecventa literei alese in cuvintele din vector).

    > Sortez vectorul de cuvinte in ordinte descrescatoare in functie de raportul dintre numarul de aparitii ale literei si lungimea cuvantului.

    > Cat timp numarul de aparitii ale literei este <= decat lungimea parolei, litera nu e inca dominanta. Scot ultimul cuvant din vector (cel mai prost), scad din lungimea parolei nr de caractere din cuvant si scad din nr de aparitii ale literei frecventa ei in acel cuvant.

    > Daca lungimea parolei devine 0, nu am putut sa fac litera dominanta in parola, returnez 0. Altfel voi returna lungimea parolei dupa ce litera a devenit dominanta.

-   int main()

    > Citesc nr de cuvinte si fiecare cuvant din fisierul de input.

    > Pe parcurs retin lungimea parolei. Consider ca parola initiala poate fi formata din concatenarea tuturor cuvintelor.

    > Generez un HashMap folosind countLetters si apelez get_password_length pentru fiecare combinatie litera-frecventa. Folosesc variabila max_password_length pentru a retine lungimea maxima a unei parole cu o litera dominanta in ea.

    > Deoarece get_password_length va fi apelata de maxim 8 ori (o data pentru fiecare litera din parola), complexitatea temporala nu e afectata.

    > Scriu max_password_length in fisierul de output.

### Complexitate temporala

    Este dominata de get_password_length.

    T(n, k) = O((n * log(n)) * k) (sortare) + O(n) (eliminare cuvinte) = O((n * log(n)) * k)
    n - nr de cuvinte
    k - nr mediu de caractere dintr-un cuvant

---

### Problema 5 - Oferta

-   const double apply_pair_discount(const unsigned int first, const unsigned int second)

    > Returneaza pretul pentru un grup de 2 produse dupa aplicarea reducerii.

-   const unsigned int apply_triple_discount(const unsigned int first, const unsigned int second, const unsigned int third)

    > Returneaza pretul pentru un grup de 3 produse dupa aplicarea reducerii.

-   double find_min_price(const unsigned int products[], const unsigned int nr_products)

    > Folosesc programare dinamica pentru a gasi pretul minim.

    > Pentru memoizarea subproblemelor folosesc un vector 1D dp. dp[i] este pretul minim pentru a cumpara primele i + 1 produse.

    > Am 3 cazuri de baza: dp[0], dp[1], dp[2]

        - dp[0] e pretul primului produs

        - dp[1] e pretul primei perechi

        - dp[2] e minimul dintre preturile pentru produs + pereche, pereche + produs, triplet.

    > Pentru cazul general (dp[i]), ma folosesc de 3 subprobleme precedente in recurenta (dp[i-1],dp[i-2],dp[i-3]). dp[i] e minimul dintre preturile pentru dp[i-1] + pretul ultimului produs, dp[i-2] + pretul ultimei perechi si dp[i-3] + pretul ultimului triplet.

    > Solutia problemei intregi e gasita in ultimul element din dp.

-   int main()

    > Citesc nr de produse, apoi pretul fiecarui produs din fisierul de input. Voi trata cazul K == 1.

    > Apelez find_min_price pentru a gasi pretul minim si il scriu in fisierul de output.

### Complexitate temporala

    Este dominata de find_min_price.

    T(n) = O(n)
    n - nr de produse

---
