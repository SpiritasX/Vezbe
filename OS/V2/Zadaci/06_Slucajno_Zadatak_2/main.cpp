/*
    Koristeći konzolu i nasumično generisane slučajne brojeve
    po normalnoj distribuciji, vizuelizovati Gausovu krivu
    koristeći zvezdice. Gausova kriva po X osi ima moguće
    vrednosti koje su generisane, a po Y osi koliko su vrednosti
    u tom delu X ose zastupljene, procentualno, u svim
    generisanim vrednostima. Za opseg Y uzmite od 0 do
    najveće izmerene vrednosti od svih Y vrednosti,
    dok za X uzmite plus-minus 2.5 standardne devijacije
    od srednje vrednosti. Veličina uzorka slučajnih vrednosti,
    tj. koliko da generišete pre nego probate neka vam je
    8192.

    Gausova kriva za srednju vrednost 5
    i standardnu devijaciju 2 izlgeda otprilike ovako ako se
    posmatra rotirano za 90 stepeni, kao u zadatku pod A:
    0-1: *
    1-2: ****
    2-3: *********
    3-4: ***************
    4-5: ******************
    5-6: *******************
    6-7: ***************
    7-8: ********
    8-9: ****
    9-10: *
    Gausova kriva ya srednju vrednost 0 i SD 1, nacrtana
    uspravno izgleda otprilike ovako:
                                        * *
                                     *  ***
                                     * ***** *
                                  *  **********
                                  *  ********** *
                              ***************** *
                            * *******************
                            *********************
                           ************************ **
                          ****************************
                         *******************************
                       * *******************************
                      ********************************** *
                    * ********************************** *
                    ****************************************
                    ******************************************
                 * *******************************************
                ************************************************
                **************************************************
            *******************************************************
            **********************************************************
       * * ************************************************************
   *  ********************************************************************
   **************************************************************************
********************************************************************************
    Odabrati jedan:
    A) (Lakše) Prikazati Gausovu krivu rotiranu za 90 stepeni.
    B) (Teže) Prikazati je normalno
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>
#include <fstream>

typedef std::chrono::high_resolution_clock hrc_t;

hrc_t::time_point start = hrc_t::now();

int main() {
	std::default_random_engine generator;

	hrc_t::duration d = hrc_t::now() - start;
	generator.seed(d.count());

	std::normal_distribution<> dist{0, 1};

  std::vector<int> brojaci(100);

  for (int i = 0; i < 1500; i++) {
    int idx = (int)std::floor(dist(generator) * 20 + 50);
    //std::cout << idx << std::endl;
    if (idx >= 0 && idx < 100)
      ++brojaci[idx];
  }

  std::ofstream output("output");

  // for (int i = 0; i < 100; i++) {
  //   output << i << "-" << i + 1 << ":";
  //   for (int j = 0; j < brojaci[i]; j++)
  //     output << "*";
  //   output << "\n";
  // }
  
  int max = *std::max_element(brojaci.begin(), brojaci.end());

  //std::cout << max;

  for (int j = max; j > 0; j--) {
    for (int i = 0; i < 100; i++) {
      if (j <= brojaci[i])
        output << "*";
      else
        output << " ";
    }
    output << std::endl;
  }

  output.close();

	return 0;
}
