#include <iostream>
#include <cstring>
#include <cstdlib>
#include <signal.h>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/moment.hpp>

using namespace std;

boost::mt19937 rng;
bool cont = true;

static int usage()
{
  cerr << "usage: dl NB BS" << endl;
  cerr << "exemple: \"dl 4 10\" for 4d10" << endl;
  return 1;
}

static void hndsi(int s)
{
  cont = false;
  cout << "Interrupting ..." << endl;
}

int main(int c, char** v)
{
  if (c != 3) 
    return usage();
  signal(SIGINT, hndsi);
  int st[4];
  memcpy(st, &v, sizeof(char***));
  rng.seed(time(0) + st[0] * st[1] + st[2] + st[3]);
  int nb = atoi(v[1]);
  int ns = atoi(v[2]);

  using namespace boost;
  uniform_int<> size(1, ns);
  variate_generator<mt19937&, uniform_int<> > die(rng, size);

  using namespace boost::accumulators;
  accumulator_set<int, features<tag::mean, tag::max, tag::median,
				tag::moment<2> > > acc;

  cout << "Generating numbers for " << nb << "d" << ns
       << ". Please hit Ctrl+C after some while." << endl;
  while (cont) {
    int max = 0;
    for (int i = 0; i < nb; ++i) {
      int p = 0;
      int pp = 0;
      do {
	p = die();
	pp += p;
      } while (p == ns);
      if (pp > max)
	max = pp;
    }
    acc(max);
  }
  cout << "Iterations: " << extract::count(acc) << endl;
  cout << "Mean: " << extract::mean(acc) << endl;
  cout << "Median: " << extract::median(acc) << endl;
  cout << "Maximum reached: " << extract::max(acc) << endl;
  cout << "Variance: " << extract::moment<2>(acc) << endl;
  return 0;
}
