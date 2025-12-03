// example: how to solve a simple explicit LP
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <vector>
#include <string>
#include <iostream>
#include <cassert>

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
  const int u  = ++vvv; vname.push_back("u"); // >=8
  const int F  = ++vvv; vname.push_back("#cells");

  // substructures of u-cells
  const int sx = ++vvv; vname.push_back("sx");
  const int s1 = ++vvv; vname.push_back("s1");
  const int s2 = ++vvv; vname.push_back("s2");
  const int s3 = ++vvv; vname.push_back("s3");

  // non-crossing edges shared by cells c5, c7, t6:
  const int e_tc5  = ++vvv; vname.push_back("noncrossing_edges_c5_t");
  const int e_tc7  = ++vvv; vname.push_back("noncrossing_edges_c7_t");
  const int e_tu   = ++vvv; vname.push_back("noncrossing_edges_u_t");
  
  const int e_c5   = ++vvv; vname.push_back("noncrossing_edges_c5_c5");
  const int e_c7   = ++vvv; vname.push_back("noncrossing_edges_c7_c7");
  const int e_u    = ++vvv; vname.push_back("noncrossing_edges_u_u");

  const int e_c5c7 = ++vvv; vname.push_back("noncrossing_edges_c5_c7");
  const int e_c5u  = ++vvv; vname.push_back("noncrossing_edges_c5_u");
  const int e_c7u  = ++vvv; vname.push_back("noncrossing_edges_c7_u");

  // wedges including 5 cells (x = c6 or u)
  const int w_55xx  = ++vvv; vname.push_back("wedge 55xx"); // a
  const int w_5xxx  = ++vvv; vname.push_back("wedge 5xxx"); // b
  const int w_5x7x  = ++vvv; vname.push_back("wedge 5x7x"); // c
  // other wedges
  const int w_xxxx = ++vvv; vname.push_back("wedge xxxx"); // d
  const int w_xxx7 = ++vvv; vname.push_back("wedge xxx7"); // e 
  const int w_xx77 = ++vvv; vname.push_back("wedge xx77"); // f
  const int w_x777 = ++vvv; vname.push_back("wedge x777"); // g 
  const int w_7777 = ++vvv; vname.push_back("wedge 7777");

  int ccc = -1;

  // all vertices have degree geq 3
  ++ccc;
  cname.push_back("3n leq 2E");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(n, ccc, 3);  
  lp.set_a(E, ccc, -2);  

  ++ccc;
  cname.push_back("w_55xx + ... leq X");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(w_55xx, ccc, 1);
  lp.set_a(w_5xxx, ccc, 1);
  lp.set_a(w_5x7x, ccc, 1);
  lp.set_a(w_xxxx, ccc, 1);
  lp.set_a(w_xxx7, ccc, 1);
  lp.set_a(w_xx77, ccc, 1);
  lp.set_a(w_x777, ccc, 1);
  lp.set_a(w_7777, ccc, 1);
  lp.set_a(X, ccc, -1);

  ++ccc;
  cname.push_back("2w_5566 + ... = c5");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(w_55xx, ccc, 2);
  lp.set_a(w_5xxx, ccc, 1);
  lp.set_a(w_5x7x, ccc, 1);
  lp.set_a(c5, ccc, -1);

  ++ccc;
  cname.push_back("2w_55xx + ... = (c6 + sx)");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(w_55xx, ccc, 2);
  lp.set_a(w_5xxx, ccc, 3);
  lp.set_a(w_5x7x, ccc, 2);
  lp.set_a(w_x777, ccc, 1);
  lp.set_a(w_xx77, ccc, 2);
  lp.set_a(w_xxx7, ccc, 3);
  lp.set_a(w_xxxx, ccc, 4);
  lp.set_a(c6, ccc, -2);
  lp.set_a(sx, ccc, -1);

  ++ccc;
  cname.push_back("w_5676 + ... = c7");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(w_5x7x, ccc, 1);
  lp.set_a(w_xxx7, ccc, 1);
  lp.set_a(w_xx77, ccc, 2);
  lp.set_a(w_x777, ccc, 3);
  lp.set_a(w_7777, ccc, 4);
  lp.set_a(c7, ccc, -1);

  // if we have 55xx wedge, we cannot have those c5's adjacent to triangle
  // if we have 55xx wedge, cannot be adjacent to another 55xx wedge
  ++ccc;
  cname.push_back("2 w55xx + e_tc5 + e_c5 leq c5");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(w_55xx, ccc, 2);
  lp.set_a(e_tc5, ccc, 1);
  lp.set_a(e_c5, ccc, 1);
  lp.set_a(c5, ccc, -1);

  //// Planarity-derived constraints
  // edge density C_{4}-free planar
  // constraint #1: E - X \leq (15/7) (n-2)
  ++ccc;
  cname.push_back("E - X leq (15/7) (n - 2)");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, -30);
  lp.set_a(E, ccc, 7);
  lp.set_a(X, ccc, -7);
  lp.set_a(n, ccc, -15);

  // constraint #2: F = (E + 2X) - (n + X) + 2
  ++ccc;
  cname.push_back("F = E + X - n + 2");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 2);
  lp.set_a(F, ccc, 1);
  lp.set_a(n, ccc, 1);
  lp.set_a(E, ccc, -1);
  lp.set_a(X, ccc, -1);

  /// Total cell counts
  /// NOTE: OUTER FACE MIGHT NOT BE COVERED BY s1,s2,s3,sx CONSTRUCTIONS
  // constraint #3: u + c5 + c6 + c7 + t6 \leq F
 ++ccc;
  cname.push_back("u + c5 + c6 + c7 + t6 leq F");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(c5, ccc, 1);
  lp.set_a(c6, ccc, 1);
  lp.set_a(c7, ccc, 1);
  lp.set_a(t6, ccc, 1);
  lp.set_a(u, ccc, 1);
  lp.set_a(F, ccc, -1);
  ++ccc;

  // constraint #4: 8 u \leq 2(s_{1,2,3}) + s_{x}
  ++ccc;
  cname.push_back("8u leq 2(s_{1,2,3}) + s_{x}");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(u, ccc, 8);
  lp.set_a(s1, ccc, -2);
  lp.set_a(s2, ccc, -2);
  lp.set_a(s3, ccc, -2);
  lp.set_a(sx, ccc, -1);

  ++ccc;
  cname.push_back("2sx = 2s3 + s2");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(sx, ccc, 2);
  lp.set_a(s2, ccc, -1);
  lp.set_a(s3, ccc, -2);



  /// Triangle count related to c5, c7, ...
  // constraint #: 3*t6 leq c5 + 2*c7 + (s1 + s2/2)
  ++ccc;
  cname.push_back("3t6 leq c5 + 2 c7 + (s_1 + s2/2)");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(t6, ccc, 6);
  lp.set_a(c5, ccc, -2);
  lp.set_a(c7, ccc, -4);
  lp.set_a(s1, ccc, -2);
  lp.set_a(s2, ccc, -1);



  //// Edge constraints
  // constraint #8: E = E_{x} + E_{p}
  ++ccc;
  cname.push_back("E = E_{x} + E_{p}");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(ep, ccc, 1);
  lp.set_a(ex, ccc, 1);
  lp.set_a(E, ccc, -1);

  // constraint #9: E_{x} = 2 X
  ++ccc;
  cname.push_back("E_{x} = 2X");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(ex, ccc, 1);
  lp.set_a(X, ccc, -2);

  // constraint #10: c5 + 2*c6 + c7 + s_{x} = 2 E_{x}
  //  [covered by constraints #5 and #9]
  ++ccc;
  cname.push_back("c5 + 2c6 + c7 + sx = 2 E_{x}");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(c5, ccc, 1);
  lp.set_a(c6, ccc, 2);
  lp.set_a(c7, ccc, 1);
  lp.set_a(sx, ccc, 1);
  lp.set_a(ex, ccc, -2);

  // constraint #11: c5 + 2*c7 + 3*t6 + (s1 + s2/2) = 2 E_{p}
  ++ccc;
  cname.push_back("c5 + 2 c7 + 3 t6 + (s1 + s2/2) = 2 E_{p}");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(c5, ccc, 2);
  lp.set_a(c7, ccc, 4);
  lp.set_a(t6, ccc, 6);
  lp.set_a(s1, ccc, 2);
  lp.set_a(s2, ccc, 1);
  lp.set_a(ep, ccc, -4);

  // constraint #12: 3*t6 \leq E_{p}
  // triangles cannot share edges
  ++ccc;
  cname.push_back("3t6 leq E_{p}");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(t6, ccc, 3);
  lp.set_a(ep, ccc, -1);


  //// Non-crossing edge constraints
  // constraint #13: e_{t c5} + e_{t c7} + e_{t u}
  //                + e_{c5 c7} + e_{c5 u} + e_{c7 u}
  //                + e_{c5} + e_{c7} + e_{u} = E_{p}
  ++ccc;
  cname.push_back("e_{t c5} + e_{t c7} + e_{c5 c7} + e_{c5 u} + ... = E_{p}");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  // triangle
  lp.set_a(e_tc5, ccc, 1);
  lp.set_a(e_tc7, ccc, 1);
  lp.set_a(e_tu, ccc, 1);
  // mixed
  lp.set_a(e_c5c7, ccc, 1);
  lp.set_a(e_c5u, ccc, 1);
  lp.set_a(e_c7u, ccc, 1);
  // cell to itself
  lp.set_a(e_c5, ccc, 1);
  lp.set_a(e_c7, ccc, 1);
  lp.set_a(e_u, ccc, 1);

  lp.set_a(ep, ccc, -1);

  // constraint #14: e_{t c5} + e_{c5 c7} + e_{c5 u} + 2 e_{c5 c5} = c5
  ++ccc;
  cname.push_back("e_{t c5} + e_{c5 c7} + e_{c5 u} + 2 e_{c5 c5} = c5");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(e_tc5, ccc, 1);
  lp.set_a(e_c5c7, ccc, 1);
  lp.set_a(e_c5u, ccc, 1);
  lp.set_a(e_c5, ccc, 2);
  lp.set_a(c5, ccc, -1);

  // constraint #15: e_{t c7} + e_{c5 c7} + e_{c7 u} + 2e_{c7 c7} = 2 c7
  ++ccc;
  cname.push_back("e_{t c7} + e_{c5 c7} + e_{c7 u} + 2 e_{c7 c7} = 2 c7");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(e_tc7, ccc, 1);
  lp.set_a(e_c5c7, ccc, 1);
  lp.set_a(e_c7u, ccc, 1);
  lp.set_a(e_c7, ccc, 2);
  lp.set_a(c7, ccc, -2);

  // constraint #17: e_{t u} + e_{c5 u} + e_{c7 u} + 2e_{u u} = s1 + s2/2
  ++ccc;
  cname.push_back("e_{t u} + e_{c5 u} + e_{c7 u} + 2e_{u u} = s1 + s2/2");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(e_tu, ccc, 2);
  lp.set_a(e_c5u, ccc, 2);
  lp.set_a(e_c7u, ccc, 2);
  lp.set_a(e_u, ccc, 4);
  lp.set_a(s1, ccc, -2);
  lp.set_a(s2, ccc, -1);

  // constraint #18: e_{t c5} + e_{t c7} + e_{t u} = 3t
  ++ccc;
  cname.push_back("e_{t c5} + e_{t c7} + e_{t u} = 3 t6");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(e_tc5, ccc, 1);
  lp.set_a(e_tc7, ccc, 1);
  lp.set_a(e_tu, ccc, 1);
  lp.set_a(t6, ccc, -3);

  // constraint #5: c7 \leq 4X
  ++ccc;
  cname.push_back("c7 leq 4X");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(c7, ccc, 1);
  lp.set_a(X, ccc, -4);
  // constraint #5: c6 \leq 2X
  ++ccc;
  cname.push_back("c6 leq 2X");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(c7, ccc, 1);
  lp.set_a(X, ccc, -2);

  
  // constraint #19: e_{t c5} \leq X
  // cell c5 adjacent to a triangle cannot "share" crossing with another c5
  ++ccc;
  cname.push_back("e_{t c5} leq X");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(e_tc5, ccc, 1);
  lp.set_a(X, ccc, -1);

  // constraint #20: c5 \leq 2X - e_{t c5} - e_{c5}
  // each crossing can give two c5's, but:
  //   - if a c5 is adjacent to a triangle, then only 1
  //   - if a c5 is adjacent to another c5 on non-crossing edge, 
  //     then only one of the two can share crossing with another c5
  //   - if a c5 is adjacent to a c7 on non-crossing edge, 
  //     then the c7 crossing can only have one c5
  // So for each edge e_{t c5}, e_{c5}, e_{c5c7}, we get crossings with at most 1 c5
  ++ccc;
  cname.push_back("c5 leq 2X - e_{t c5} - e_{c5} - e_{c5 c7}");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(c5, ccc, 1);
  lp.set_a(e_tc5, ccc, 1);
  lp.set_a(e_c5, ccc, 1);
  lp.set_a(e_c5c7, ccc, 1);
  lp.set_a(X, ccc, -2);

  // if we have 55xx wedge, we cannot have those c5's adjacent to triangle
  // if we have 55xx wedge, cannot be adjacent to another 5566 wedge
  ++ccc;
  cname.push_back("2 w55xx + e_tc5 + e_c5 leq c5");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(w_55xx, ccc, 2);
  lp.set_a(e_tc5, ccc, 1);
  lp.set_a(e_c5, ccc, 1);
  lp.set_a(c5, ccc, -1);

  // constraint #21: edge density formula
  ++ccc;
  cname.push_back("E leq 2.4(n-2) + ...");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, -96);
  lp.set_a(E, ccc, 20);
  lp.set_a(n, ccc, -48);
  lp.set_a(c5, ccc, -13);
  lp.set_a(c6, ccc, -6);
  lp.set_a(t6, ccc, -6);
  lp.set_a(c7, ccc, 1);
  lp.set_a(u, ccc, 8);
  lp.set_a(X, ccc, 20);

  const double factor = 10.0;
  // constraint #: normalize (n-2)=factor
  ++ccc;
  cname.push_back("normalize: (n-2)=factor");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, factor+2);
  lp.set_a(n, ccc, 1);

  // objective function: set to minimize -E
  //                        <=> maximize E
  lp.set_c(E, -1);

  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));

  // output solution
  if (s.is_unbounded()) {
    std::cout << "unbounded\n" << std::endl;
    std::cout << "base point:\n\n";
    int j = 0;
    for (auto xit = s.variable_values_begin(); xit != s.variable_values_end(); ++xit, ++j) {
      std::cout << "[" << vname[j] << "] = " << *xit << "\n";
      if (j == 4 || j == 10 || j == 14 || j == 23) std::cout << "\n";
    }

    std::cout << "\n\n\n\ndirection:\n\n";
    auto it = s.unboundedness_certificate_begin(); int i = 0;
    for (; it != s.unboundedness_certificate_end(); ++it, ++i) {
      std::cout << "w[" << vname[i] << "] = " << *it << "\n";
      if (i == 4 || i == 10 || i == 14 || i == 23) std::cout << "\n";
    }
  }
  else if (s.is_infeasible()) {
    std::cout << "infeasible\n";

    std::cout << "Constraints used in infeasibility certificate:\n";
    std::size_t c = 0;
    for (auto it = s.infeasibility_certificate_begin();
    it != s.infeasibility_certificate_end(); ++it, ++c)
    {
      if (*it != 0) {
        std::cout << "  lambda[" << c << "] = " << *it
          << "  ->  " << cname[c] << "\n";
      }
    }
  }
  else if (!s.is_optimal()) std::cout << "no optimal solution" << std::endl;
  else {
    std::cout << "|E| leq " 
              << -s.objective_value()/factor << "n"
              << " (about " << -(CGAL::to_double(s.objective_value())/factor) << ")\n\n";

    // variables
    std::vector<ET> val(s.variable_numerators_begin(), s.variable_numerators_end());
    for (std::size_t i = 0; i < val.size(); ++i) {
      std::cout << vname[i] << " = " << val[i] << "\n";
      if (i == 4 || i == 10 || i == 14 || i == 23) std::cout << "\n";
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
