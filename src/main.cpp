// example: how to solve a simple explicit LP
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <vector>
#include <string>

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main()
{
  // create an LP with Ax <= b, lower bound 0 and no upper bounds
  Program lp(CGAL::SMALLER, true, 0, false, 1000); 

  // names
  std::vector<std::string> vname; // variables
  std::vector<std::string> cname; // constraints

  // variables
  int vvv = -1;
  const int n = ++vvv; vname.push_back("#num_vertices"); // lower bound
  const int X = ++vvv; vname.push_back("#crossings");
  const int E = ++vvv; vname.push_back("#edges");
  // types of edges
  const int ep = ++vvv; vname.push_back("#noncrossing_edges"); // no crossing
  const int ex = ++vvv; vname.push_back("#crossing_edges"); // one crossing

  // #cells of certain type
  const int c5 = ++vvv; vname.push_back("c5");
  const int c6 = ++vvv; vname.push_back("c6");
  const int c7 = ++vvv; vname.push_back("c7");
  const int t6 = ++vvv; vname.push_back("t6");
  const int c8 = ++vvv; vname.push_back("c8");
  const int u  = ++vvv; vname.push_back("u");
  const int sx = ++vvv; vname.push_back("sx");
  const int s1 = ++vvv; vname.push_back("s1");
  const int s2 = ++vvv; vname.push_back("s2");
  const int s3 = ++vvv; vname.push_back("s3");

  // non-crossing edges shared by cells c5, c7, t6:
  const int e_c5 = ++vvv; vname.push_back("noncrossing_edges_c5_c5");
  const int e_c7 = ++vvv; vname.push_back("noncrossing_edges_c7_c7");
  const int e_c8 = ++vvv; vname.push_back("noncrossing_edges_c8_c8");
  const int e_tc5 = ++vvv; vname.push_back("noncrossing_edges_c5_t");
  const int e_tc7 = ++vvv; vname.push_back("noncrossing_edges_c7_t");
  const int e_tc8 = ++vvv; vname.push_back("noncrossing_edges_c8_t");
  const int e_c5c7 = ++vvv; vname.push_back("noncrossing_edges_c5_c7");
  const int e_c5c8 = ++vvv; vname.push_back("noncrossing_edges_c5_c8");
  const int e_c7c8 = ++vvv; vname.push_back("noncrossing_edges_c7_c8");

  // -----------------------------------------------------------------------------------------------
  // global assumption: no >=7 cell
  // -----------------------------------------------------------------------------------------------

  // -----------------------------------------------------------------------------------------------
  // trivial or known constraints
  // -----------------------------------------------------------------------------------------------

  int ccc = -1;

  ++ccc;
  cname.push_back("E - X leq 3n - 6");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, -6);
  lp.set_a(E, ccc, 1);
  lp.set_a(X, ccc, -1);
  lp.set_a(X, ccc, -1);
  lp.set_a(n, ccc, -3);

  ///// Cell counts related to crossing number
  // constraint #0: c5 \leq 2X
  ++ccc;
  cname.push_back("c5 leq 2X");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(c5, ccc, 1);
  lp.set_a(X, ccc, -2);

  // constraint #1: c6 \leq 2X
  ++ccc;
  cname.push_back("c6 leq 2X");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(c6, ccc, 1);
  lp.set_a(X, ccc, -2);

  // constraint #2: c7 \leq 4X
  ++ccc;
  cname.push_back("c7 leq 4X");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(c7, ccc, 1);
  lp.set_a(X, ccc, -4);

  // constraint #: c8 \leq X
  ++ccc;
  cname.push_back("c8 leq 2X");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(c7, ccc, 1);
  lp.set_a(X, ccc, -2);

  ///// Triangle count related to c5, c7, c8
  // constraint #3: 3*t6 \leq c5 + 2*c7 + c8
  ++ccc;
  cname.push_back("3t6 leq c5 + 2 c7 + c8");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(t6, ccc, 3);
  lp.set_a(c5, ccc, -1);
  lp.set_a(c7, ccc, -2);
  lp.set_a(c8, ccc, -1);


  ///// Edge constraints
  // constraint #4: E = E_{x} + E_{p}
  ++ccc;
  cname.push_back("E = E_{x} + E_{p}");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(ep, ccc, 1);
  lp.set_a(ex, ccc, 1);
  lp.set_a(E, ccc, -1);

  // constraint #5: E_{x} = 2 X
  ++ccc;
  cname.push_back("E_{x} = 2X");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(ex, ccc, 1);
  lp.set_a(X, ccc, -2);

  // constraint #6: c5 + 2*c6 + c7 + 2 c8 \leq E_{x}
  ++ccc;
  cname.push_back("c5+2c6+c7+2c8 leq E_{x}");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(c5, ccc, 1);
  lp.set_a(c6, ccc, 2);
  lp.set_a(c7, ccc, 1);
  lp.set_a(c8, ccc, 2);
  lp.set_a(ex, ccc, -1);

  // constraint #7: c5 + 2*c7 + 3*t6 + c8 \leq 2 E_{p}
  ++ccc;
  cname.push_back("A + 2C + 3T leq 2 E_{p}");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(c5, ccc, 1);
  lp.set_a(c7, ccc, 2);
  lp.set_a(t6, ccc, 3);
  lp.set_a(c8, ccc, 1);
  lp.set_a(ep, ccc, -2);

  // constraint #8: 3*t6 \leq E_{p}
  ++ccc;
  cname.push_back("3T leq 2 E_{p}");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(t6, ccc, 3);
  lp.set_a(ep, ccc, -2);


  ///// Non-crossing edge constraints
  // constraint #9: e_{t c5} + e_{t c7} + e_{t c8}
  //                + e_{c5 c7} + e_{c5 c8} + e_{c7 c8}
  //                + e_{c5} + e_{c7} + e_{c8} \leq E_{p}
  ++ccc;
  cname.push_back("e_{t c5} + e_{t c7} + e_{t c8} + e_{c5 c7} + e_{c5 c7} + e_{c5 c8} + ... = E_{p}");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(e_tc5, ccc, 1);
  lp.set_a(e_tc7, ccc, 1);
  lp.set_a(e_tc8, ccc, 1);

  lp.set_a(e_c5c7, ccc, 1);
  lp.set_a(e_c5c8, ccc, 1);
  lp.set_a(e_c7c8, ccc, 1);

  lp.set_a(e_c5, ccc, 1);
  lp.set_a(e_c7, ccc, 1);
  lp.set_a(e_c8, ccc, 1);

  lp.set_a(ep, ccc, -1);

  // constraint #10: e_{t c5} + e_{c5 c7} + e_{c5 c8} + 2 e_{c5 c5} \leq c5
  ++ccc;
  cname.push_back("e_{t c5} + e_{c5 c7} + 2 e_{c5 c5} leq c5");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(e_tc5, ccc, 1);
  lp.set_a(e_c5c7, ccc, 1);
  lp.set_a(e_c5c8, ccc, 1);
  lp.set_a(e_c5, ccc, 2);
  lp.set_a(c5, ccc, -1);

  // constraint #11: e_{t c7} + e_{c5 c7} + e_{c7 c8} + 2e_{c7 c7} \leq 2 c7
  ++ccc;
  cname.push_back("e_{t c7} + e_{c5 c7} + e_{c7 c7} leq 2 c7");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(e_tc7, ccc, 1);
  lp.set_a(e_c5c7, ccc, 1);
  lp.set_a(e_c7c8, ccc, 1);
  lp.set_a(e_c7, ccc, 2);
  lp.set_a(c7, ccc, -2);

  // constraint #: e_{t c8} + e_{c5 c8} + e_{c7 c8} + 2e_{c8 c8} \leq c8
  ++ccc;
  cname.push_back("e_{t c8} + e_{c5 c8} + e_{c7 c8} + 2e_{c8 c8} leq c8");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(e_tc8, ccc, 1);
  lp.set_a(e_c5c8, ccc, 1);
  lp.set_a(e_c7c8, ccc, 1);
  lp.set_a(e_c8, ccc, 2);
  lp.set_a(c8, ccc, -1);

  // constraint #12: e_{t c5} + e_{t c7} + e_{t c8} \leq 3t
  ++ccc;
  cname.push_back("e_{t c5} + e_{t c7} leq 3 t6");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(e_tc5, ccc, 1);
  lp.set_a(e_tc7, ccc, 1);
  lp.set_a(e_tc8, ccc, 1);
  lp.set_a(t6, ccc, -3);

  // constraint #13: e_{t c5} \leq X
  // cell c5 adjacent to a triangle cannot "share" crossing with another c5
  ++ccc;
  cname.push_back("e_{t c5} leq X");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(e_tc5, ccc, 1);
  lp.set_a(X, ccc, -1);

  // constraint #14: c5 \leq 2X - e_{t c5} - e_{c5}
  // each crossing can give two c5's, but:
  //   - if a c5 is adjacent to a triangle, then only 1
  //   - if a c5 is adjacent to another c5 on non-crossing edge, 
  //     then only one of the two can share crossing with another c5
  //   - if a c5 is adjacent to a c7 on non-crossing edge, 
  //     then the c7 crossing can only have one c5
  // So for each edge e_{t c5}, e_{c5}, e_{c7}, we get crossings with at most 1 c5
  ++ccc;
  cname.push_back("c5 leq 2X - e_{t c5} - e_{c5} - e_{c5 c7}");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(c5, ccc, 1);
  lp.set_a(e_tc5, ccc, 1);
  lp.set_a(e_c5, ccc, 1);
  lp.set_a(e_c5c7, ccc, 1);
  lp.set_a(X, ccc, -2);

  // constraint #[-1]: normalization: X = 1
  ++ccc;
  cname.push_back("Normalize: X = 1");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 1);
  lp.set_a(X, ccc, 1);

  // objective function: set to minimize -13 c5 - 6 c6 - 6 t6 + c7 + 8 c8  + 15u + 20X 
  //                        <=> maximize 13 c5 + 6 c6 + 6 t6 - c7 - 8 c8 - 15u - 20X 
  lp.set_c(c5, -13);
  lp.set_c(c6, -6);
  lp.set_c(t6, -6);
  lp.set_c(c7, 1);
  lp.set_c(c8, 8);
  lp.set_c(u, 15);
  lp.set_c(X, 20);

  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));

  // output solution
  if (s.is_unbounded()) std::cout << "unbounded" << std::endl;
  else if (s.is_infeasible()) std::cout << "infeasible" << std::endl;
  else if (!s.is_optimal()) std::cout << "no optimal solustion" << std::endl;
  else {
    std::cout << "Max value of 13c5 + 6c6 + 6t6 - c7 - 8c8 - 20X: " 
              << -s.objective_value()
              << " (about " << -CGAL::to_double(s.objective_value()) << ")\n\n";

    // variables
    std::vector<ET> val(s.variable_numerators_begin(), s.variable_numerators_end());
    for (std::size_t i = 0; i < val.size(); ++i) {
      std::cout << vname[i] << " = " << val[i] << "\n";
      if (i == 4) std::cout << "\n";
      else if (i == 9) std::cout << "\n";
    }

    // tight constraints
    std::cout << "\nTight constraints:\n";
    std::size_t c = 0;
    for (auto i = s.optimality_certificate_begin(); i != s.optimality_certificate_end(); ++i) {
      if (*i != 0) std::cout << "  " << cname[c] << "\n";
      ++c;
    }

  }

}
