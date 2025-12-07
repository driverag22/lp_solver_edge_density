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
  // create an LP with Ax <= b, lower bound 0 and no upper bounds on variables
  Program lp(CGAL::SMALLER, true, 0, false, 1000); 

  // names
  std::vector<std::string> vname; // variables
  std::vector<std::string> cname; // constraints

  // variables
  int vvv = -1;
  const int n = ++vvv; vname.push_back("#num_vertices");
  const int n3 = ++vvv; vname.push_back("#num_vertices_deg_3");
  const int n4 = ++vvv; vname.push_back("#num_vertices_deg_4");
  const int n5 = ++vvv; vname.push_back("#num_vertices_deg_5");
  const int n6 = ++vvv; vname.push_back("#num_vertices_deg_geq_6");
  
  const int F  = ++vvv; vname.push_back("#cells");
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

  // non-crossing edges shared by cells c5, c7, t6:
  const int e_tc5  = ++vvv; vname.push_back("noncrossing_edges_c5_t");
  const int e_tc7  = ++vvv; vname.push_back("noncrossing_edges_c7_t");
  
  const int e_c5   = ++vvv; vname.push_back("noncrossing_edges_c5_c5");
  const int e_c7   = ++vvv; vname.push_back("noncrossing_edges_c7_c7");

  const int e_c5c7 = ++vvv; vname.push_back("noncrossing_edges_c5_c7");

  // wedges including 5 cells
  const int w_5566 = ++vvv; vname.push_back("wedge 5566"); // a
  const int w_5676 = ++vvv; vname.push_back("wedge 5676"); // b
  const int w_5666 = ++vvv; vname.push_back("wedge 5666"); // c
  // other wedges
  const int w_6666 = ++vvv; vname.push_back("wedge 6666"); // d
  const int w_6667 = ++vvv; vname.push_back("wedge 6667"); // e 
  const int w_6677 = ++vvv; vname.push_back("wedge 6677"); // f
  const int w_6777 = ++vvv; vname.push_back("wedge 6777"); // g 
  const int w_7777 = ++vvv; vname.push_back("wedge 7777");

  // wedges counting for each c6
  const int w_ac = ++vvv; vname.push_back("wedge 5566 to 5666");
  const int w_ad = ++vvv; vname.push_back("wedge 5566 to 6666");
  const int w_ae = ++vvv; vname.push_back("wedge 5566 to 6667");
  const int w_af = ++vvv; vname.push_back("wedge 5566 to 6677");
  const int w_ag = ++vvv; vname.push_back("wedge 5566 to 6777");
  const int w_bc = ++vvv; vname.push_back("wedge 5676 to 5666");
  const int w_bd = ++vvv; vname.push_back("wedge 5676 to 6666");
  const int w_be = ++vvv; vname.push_back("wedge 5676 to 6667");
  const int w_bf = ++vvv; vname.push_back("wedge 5676 to 6677");
  const int w_bg = ++vvv; vname.push_back("wedge 5676 to 6777");
  const int w_cc = ++vvv; vname.push_back("wedge 5666 to 5666");
  const int w_cd = ++vvv; vname.push_back("wedge 5666 to 6666");
  const int w_ce = ++vvv; vname.push_back("wedge 5666 to 6667");
  const int w_cf = ++vvv; vname.push_back("wedge 5666 to 6677");
  const int w_cg = ++vvv; vname.push_back("wedge 5666 to 6777");
  const int w_dd = ++vvv; vname.push_back("wedge 6666 to 6666");
  const int w_de = ++vvv; vname.push_back("wedge 6666 to 6667");
  const int w_df = ++vvv; vname.push_back("wedge 6666 to 6677");
  const int w_dg = ++vvv; vname.push_back("wedge 6666 to 6777");
  const int w_ee = ++vvv; vname.push_back("wedge 6667 to 6667");
  const int w_ef = ++vvv; vname.push_back("wedge 6667 to 6677");
  const int w_eg = ++vvv; vname.push_back("wedge 6667 to 6777");
  const int w_ff = ++vvv; vname.push_back("wedge 6677 to 6677");
  const int w_fg = ++vvv; vname.push_back("wedge 6677 to 6777");
  const int w_gg = ++vvv; vname.push_back("wedge 6777 to 6777");

  const int c7_full_tr = ++vvv; vname.push_back("c7 adj to edges from same triangle");
  const int c7_partial_tr = ++vvv; vname.push_back("c7 adj to edges from single triangle");
  const int c7_arr = ++vvv; vname.push_back("c7 adj to edges from same arrow");
  const int c7_e = ++vvv; vname.push_back("c7 adj to edges from c5 but not same arrow");

  int ccc = -1;

  // every arrow leads to two c7s
  ++ccc;
  cname.push_back("w5566 leq c7");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(w_5566, ccc, 1);  
  lp.set_a(c7, ccc, -1);  

  // vertices
  ++ccc;
  cname.push_back("n3+n4+n5+n6 = n");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(n3, ccc, 1);  
  lp.set_a(n4, ccc, 1);  
  lp.set_a(n5, ccc, 1);  
  lp.set_a(n6, ccc, 1);  
  lp.set_a(n, ccc, -1);  

  // // handshake lemma
  // ++ccc;
  // cname.push_back("3 n3 + 4 n4 + 5 n5 + 6 n6 leq 2E");
  // lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  // lp.set_a(n3, ccc, 3);  
  // lp.set_a(n4, ccc, 4);  
  // lp.set_a(n5, ccc, 5);  
  // lp.set_a(n6, ccc, 6);  
  // lp.set_a(E, ccc, -2);  


  // removing crossings and triangulating
  ++ccc;
  cname.push_back("2E - 4X + 4 w_{5566} + ... = 6n - 12");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, -12);
  lp.set_a(E, ccc, 2);   
  lp.set_a(X, ccc, -4);   
  lp.set_a(w_5566, ccc, 4);   
  lp.set_a(w_5676, ccc, 6);   
  lp.set_a(w_5666, ccc, 5);   
  lp.set_a(w_6666, ccc, 6);   
  lp.set_a(w_6667, ccc, 7);   
  lp.set_a(w_6677, ccc, 8);   
  lp.set_a(w_6777, ccc, 9);   
  lp.set_a(w_7777, ccc, 10);   
  lp.set_a(n, ccc, -6);  

  // one c6-type per c6 cell
  ++ccc;
  cname.push_back("w_ac + ... = c6");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(w_ac, ccc, 1);
  lp.set_a(w_ad, ccc, 1);
  lp.set_a(w_ae, ccc, 1);
  lp.set_a(w_af, ccc, 1);
  lp.set_a(w_ag, ccc, 1);
  lp.set_a(w_bc, ccc, 1);
  lp.set_a(w_bd, ccc, 1);
  lp.set_a(w_be, ccc, 1);
  lp.set_a(w_bf, ccc, 1);
  lp.set_a(w_bg, ccc, 1);
  lp.set_a(w_cc, ccc, 1);
  lp.set_a(w_cd, ccc, 1);
  lp.set_a(w_ce, ccc, 1);
  lp.set_a(w_cf, ccc, 1);
  lp.set_a(w_cg, ccc, 1);
  lp.set_a(w_dd, ccc, 1);
  lp.set_a(w_de, ccc, 1);
  lp.set_a(w_df, ccc, 1);
  lp.set_a(w_dg, ccc, 1);
  lp.set_a(w_ee, ccc, 1);
  lp.set_a(w_ef, ccc, 1);
  lp.set_a(w_eg, ccc, 1);
  lp.set_a(w_ff, ccc, 1);
  lp.set_a(w_fg, ccc, 1);
  lp.set_a(w_gg, ccc, 1);
  lp.set_a(c6, ccc, -1);

  //// per wedge c6 constraints
  /// w_5566 = a
  ++ccc;
  cname.push_back("2 w_5566 = 2a = sum_i w_ai");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(w_ac, ccc, 1);
  lp.set_a(w_ad, ccc, 1);
  lp.set_a(w_ae, ccc, 1);
  lp.set_a(w_af, ccc, 1);
  lp.set_a(w_ag, ccc, 1);
  lp.set_a(w_5566, ccc, -2);
  /// w_5676 = b
  ++ccc;
  cname.push_back("2b = sum_i w_bi");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(w_bc, ccc, 1);
  lp.set_a(w_bd, ccc, 1);
  lp.set_a(w_be, ccc, 1);
  lp.set_a(w_bf, ccc, 1);
  lp.set_a(w_bg, ccc, 1);
  lp.set_a(w_5676, ccc, -2);
  /// w_5666 = c
  ++ccc;
  cname.push_back("3c = sum_i w_ci");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(w_ac, ccc, 1);
  lp.set_a(w_bc, ccc, 1);
  lp.set_a(w_cc, ccc, 2);
  lp.set_a(w_cd, ccc, 1);
  lp.set_a(w_ce, ccc, 1);
  lp.set_a(w_cf, ccc, 1);
  lp.set_a(w_cg, ccc, 1);
  lp.set_a(w_5666, ccc, -3);
  // each c wedge can only combine with at most one a or b wedge
  cname.push_back("w_ac + w_bc leq w_5666 = c");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(w_ac, ccc, 1);
  lp.set_a(w_bc, ccc, 1);
  lp.set_a(w_5666, ccc, -1);
  /// w_6666 = d
  ++ccc;
  cname.push_back("4d = sum_i w_di");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(w_ad, ccc, 1);
  lp.set_a(w_bd, ccc, 1);
  lp.set_a(w_cd, ccc, 1);
  lp.set_a(w_dd, ccc, 2);
  lp.set_a(w_de, ccc, 1);
  lp.set_a(w_df, ccc, 1);
  lp.set_a(w_dg, ccc, 1);
  lp.set_a(w_6666, ccc, -4);
  /// w_6667 = e
  ++ccc;
  cname.push_back("3e = sum_i w_ei");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(w_ae, ccc, 1);
  lp.set_a(w_be, ccc, 1);
  lp.set_a(w_ce, ccc, 1);
  lp.set_a(w_de, ccc, 1);
  lp.set_a(w_ee, ccc, 2);
  lp.set_a(w_ef, ccc, 1);
  lp.set_a(w_eg, ccc, 1);
  lp.set_a(w_6667, ccc, -3);
  /// w_6677 = f
  ++ccc;
  cname.push_back("2f = sum_i w_fi");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(w_af, ccc, 1);
  lp.set_a(w_bf, ccc, 1);
  lp.set_a(w_cf, ccc, 1);
  lp.set_a(w_df, ccc, 1);
  lp.set_a(w_ef, ccc, 1);
  lp.set_a(w_ff, ccc, 2);
  lp.set_a(w_fg, ccc, 1);
  lp.set_a(w_6677, ccc, -2);
  /// w_6777 = g
  ++ccc;
  cname.push_back("g = sum_i w_gi");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(w_ag, ccc, 1);
  lp.set_a(w_bg, ccc, 1);
  lp.set_a(w_cg, ccc, 1);
  lp.set_a(w_dg, ccc, 1);
  lp.set_a(w_eg, ccc, 1);
  lp.set_a(w_fg, ccc, 1);
  lp.set_a(w_gg, ccc, 2);
  lp.set_a(w_6777, ccc, -1);

  ++ccc;
  cname.push_back("w_5566 + ... = X");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(w_5566, ccc, 1);
  lp.set_a(w_5666, ccc, 1);
  lp.set_a(w_5676, ccc, 1);
  lp.set_a(w_6666, ccc, 1);
  lp.set_a(w_6667, ccc, 1);
  lp.set_a(w_6677, ccc, 1);
  lp.set_a(w_6777, ccc, 1);
  lp.set_a(w_7777, ccc, 1);
  lp.set_a(X, ccc, -1);

  ++ccc;
  cname.push_back("2w_5566 + ... = c5");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(w_5566, ccc, 2);
  lp.set_a(w_5666, ccc, 1);
  lp.set_a(w_5676, ccc, 1);
  lp.set_a(c5, ccc, -1);

  ++ccc;
  cname.push_back("2w_5566 + ... = 2 c6");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(w_5566, ccc, 2);
  lp.set_a(w_5666, ccc, 3);
  lp.set_a(w_5676, ccc, 2);
  lp.set_a(w_6666, ccc, 4);
  lp.set_a(w_6667, ccc, 3);
  lp.set_a(w_6677, ccc, 2);
  lp.set_a(w_6777, ccc, 1);
  lp.set_a(c6, ccc, -2);

  ++ccc;
  cname.push_back("w_5676 + ... = c7");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(w_5676, ccc, 1);
  lp.set_a(w_6667, ccc, 1);
  lp.set_a(w_6677, ccc, 2);
  lp.set_a(w_6777, ccc, 3);
  lp.set_a(w_7777, ccc, 4);
  lp.set_a(c7, ccc, -1);


  //// Planarity-derived constraints
  // constraint #0: E - X \leq (15/7) (n-2)
  ++ccc;
  cname.push_back("E - X leq (15/7) (n - 2)");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, -30);
  lp.set_a(E, ccc, 7);
  lp.set_a(X, ccc, -7);
  lp.set_a(n, ccc, -15);

  // constraint #1: F = (m + 2X) - (n + X) + 2
  ++ccc;
  cname.push_back("F = m + X - n + 2");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 2);
  lp.set_a(F, ccc, 1);
  lp.set_a(n, ccc, 1);
  lp.set_a(E, ccc, -1);
  lp.set_a(X, ccc, -1);

  /// Total cell counts
  // constraint #2: c5 + c6 + c7 + t6 = F
  ++ccc;
  cname.push_back("c5 + c6 + c7 + t6 = F");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(c5, ccc, 1);
  lp.set_a(c6, ccc, 1);
  lp.set_a(c7, ccc, 1);
  lp.set_a(t6, ccc, 1);
  lp.set_a(F, ccc, -1);


  /// Cell count related to crossing number
  // constraint #: c5 \leq 2X
  ++ccc;
  cname.push_back("c5 leq 2X");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(c5, ccc, 1);
  lp.set_a(X, ccc, -2);
  /// Cell count related to crossing number
  // constraint #: c6 \leq 2X
  ++ccc;
  cname.push_back("c6 leq 2X");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(c6, ccc, 1);
  lp.set_a(X, ccc, -2);
   /// Cell count related to crossing number
  // constraint #: c7 \leq 4X
  ++ccc;
  cname.push_back("c7 leq 4X");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(c6, ccc, 1);
  lp.set_a(X, ccc, -4);


  //// Edge constraints
  // constraint #4: E = e_{x} + e_{p}
  ++ccc;
  cname.push_back("E = e_{x} + e_{p}");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(ep, ccc, 1);
  lp.set_a(ex, ccc, 1);
  lp.set_a(E, ccc, -1);

  // constraint #5: e_{x} = 2 X
  ++ccc;
  cname.push_back("e_{x} = 2X");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(ex, ccc, 1);
  lp.set_a(X, ccc, -2);

  // constraint #6: c5 + 2*c6 + c7 leq 4X = 2 e_x
  ++ccc;
  cname.push_back("c5 + 2c6 + c7 = 4X");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(c5, ccc, 1);
  lp.set_a(c6, ccc, 2);
  lp.set_a(c7, ccc, 1);
  lp.set_a(X, ccc, -4);

  // constraint #7: c5 + 2*c7 + 3*t6 \leq 2 e_{p}
  ++ccc;
  cname.push_back("c5 + 2c7 + 3t6 = 2e_{p}");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(c5, ccc, 1);
  lp.set_a(c7, ccc, 2);
  lp.set_a(t6, ccc, 3);

  lp.set_a(ep, ccc, -2);



  //// Non-crossing edge constraints
  // constraint #8: e_{t c5} + e_{t c7} + e_{c5 c7} + e_{c5} + e_{c7} \leq e_{p}
  ++ccc;
  cname.push_back("e_{t c5} + e_{t c7} + e_{c5 c7} + e_{c5} + e_{c7} leq e_{p}");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(e_tc5, ccc, 1);
  lp.set_a(e_tc7, ccc, 1);
  lp.set_a(e_c5c7, ccc, 1);
  lp.set_a(e_c5, ccc, 1);
  lp.set_a(e_c7, ccc, 1);

  lp.set_a(ep, ccc, -1);

  // constraint #9: e_{t c5} + e_{c5 c7} + 2 e_{c5 c5} = c5
  ++ccc;
  cname.push_back("e_{t c5} + e_{c5 c7} + 2 e_{c5 c5} = c5");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(e_tc5, ccc, 1);
  lp.set_a(e_c5c7, ccc, 1);
  lp.set_a(e_c5, ccc, 2);

  lp.set_a(c5, ccc, -1);

  // constraint #10: e_{t c7} + e_{c5 c7} + 2e_{c7} = 2 c7
  ++ccc;
  cname.push_back("e_{t c7} + e_{c5 c7} + 2e_{c7} = 2 c7");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(e_tc7, ccc, 1);
  lp.set_a(e_c5c7, ccc, 1);
  lp.set_a(e_c7, ccc, 2);

  lp.set_a(c7, ccc, -2);

  // constraint #11: e_{t c5} + e_{t c7} = 3t
  ++ccc;
  cname.push_back("e_{t c5} + e_{t c7} leq 3 t6");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, 0);
  lp.set_a(e_tc5, ccc, 1);
  lp.set_a(e_tc7, ccc, 1);
  lp.set_a(t6, ccc, -3);

  // constraint #20: c5 \leq 2X - e_{t c5} - e_{c5} - e_{c5 c7}
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

  // if we have 5566 wedge, we cannot have those c5's adjacent to triangle
  // if we have 5566 wedge, cannot be adjacent to another 5566 wedge
  ++ccc;
  cname.push_back("2 w5566 + e_tc5 + e_c5 leq c5");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  lp.set_a(w_5566, ccc, 2);
  lp.set_a(e_tc5, ccc, 1);
  lp.set_a(e_c5, ccc, 1);
  lp.set_a(c5, ccc, -1);

  // constraint #: divide t-c7 edges into two cases:
  //     - c7 adjacent to a single triangle (two edges)
  //     - c7 adjacent to separate triangles (one edge for each)
  ++ccc;
  cname.push_back("e_tc7 = 2 c7_tr + c7_2tr");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc,0);
  lp.set_a(e_tc7, ccc, 1);
  lp.set_a(c7_full_tr, ccc, -2);
  lp.set_a(c7_partial_tr, ccc, -1);
  // constraint #: divide c5-c7 edges into two cases:
  //     - c7 adjacent to a single arrow (two edges)
  //     - any other c5-c7 edge (one edge)
  ++ccc;
  cname.push_back("e_c5c7 = 2c7_arr + c7_e");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc,0);
  lp.set_a(e_c5c7, ccc, 1);
  lp.set_a(c7_arr, ccc, -2);
  lp.set_a(c7_e, ccc, -1);

  //  - c7_full_tr gives two c7-adjacent edges
  //  - c7_partial_tr gives one
  //  - c7_arr gives two 
  //  - c7_e gives one
  //  - e_c7 gives two (edge between two c7s)
  //  - each c7 has two edges
  ++ccc;
  cname.push_back("2c7_tr + c7_2tr + 2 c7_arr + c7_e + 2 e_c7 = 2c7");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc,0);
  lp.set_a(c7_full_tr, ccc, 2);
  lp.set_a(c7_partial_tr, ccc, 1);
  lp.set_a(c7_arr, ccc, 2);
  lp.set_a(c7_e, ccc, 1);
  lp.set_a(e_c7, ccc, 2);
  lp.set_a(c7, ccc, -2);

  // c7 adjacent to single triangle cannot be on 5676 wedge
  // c7 adjacent to single arrow cannot be on 5676 wedge
  ++ccc;
  cname.push_back("w_5676 leq c7 - c7_full_tr - c7_arr");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc,0);
  lp.set_a(w_5676, ccc, 1);
  lp.set_a(c7_full_tr, ccc, 1);
  lp.set_a(c7_arr, ccc, 1);
  lp.set_a(c7, ccc, -1);

  // c7_arr appears at most once per arrow
  ++ccc;
  cname.push_back("c7_arr leq w5566");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc,0);
  lp.set_a(c7_arr, ccc, 1);
  lp.set_a(w_5566, ccc, -1);

  // c5's on arrow cannot be adjacent to triangle
  ++ccc;
  cname.push_back("e_tc5 leq c5 - 2w_5566");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc,0);
  lp.set_a(e_tc5, ccc, 1);
  lp.set_a(c5, ccc, -1);
  lp.set_a(w_5566, ccc, 2);



  // constraint #: edge density formula
  ++ccc;
  cname.push_back("E leq 2.4(n-2) + ...");
  lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, -96);
  lp.set_a(E, ccc, 20);
  lp.set_a(n, ccc, -48);
  lp.set_a(c5, ccc, -13);
  lp.set_a(c6, ccc, -6);
  lp.set_a(t6, ccc, -6);
  lp.set_a(c7, ccc, 1);
  lp.set_a(X, ccc, 20);

  // ++ccc;
  // cname.push_back("w_5676 leq c7 - 2 e_c5c7");
  // lp.set_r(ccc, CGAL::SMALLER); lp.set_b(ccc, 0);
  // lp.set_a(e_c5c7, ccc, 2);
  // lp.set_a(w_5676, ccc, 1);
  // lp.set_a(c7, ccc, -1);

  // constraint #: normalize (n-2)=1
  const double factor = 10.0;
  ++ccc;
  cname.push_back("n-2=factor");
  lp.set_r(ccc, CGAL::EQUAL); lp.set_b(ccc, (factor+2));
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
    int i = 0;
    for (auto xit = s.variable_values_begin(); xit != s.variable_values_end(); ++xit, ++i) {
      std::cout << "[" << vname[i] << "] = " << *xit << "\n";
      if (i == 4 || i == 9 || i == 13 || i == 18) std::cout << "\n";
    }
    std::cout << "\n\n\n\ndirection:\n\n";
    i = 0;
    for (auto it = s.unboundedness_certificate_begin(); it != s.unboundedness_certificate_end(); ++it, ++i) {
      std::cout << "[" << vname[i] << "] = " << *it << "\n";
      if (i == 4 || i == 9 || i == 13 || i == 18) std::cout << "\n";
    }
  }
  else if (s.is_infeasible()) std::cout << "infeasible" << std::endl;
  else if (!s.is_optimal()) std::cout << "no optimal solustion" << std::endl;
  else {
    // std::cout << "Max value of 13c5 + 6c6 + 6t6 - c7 - 8c8  - 15u - 20X: " 
    std::cout << "|E| leq " 
              << -(s.objective_value()/factor) << "n"
              << " (about " << -CGAL::to_double(s.objective_value())/factor << ")\n\n";

    // variables
    std::vector<ET> val(s.variable_numerators_begin(), s.variable_numerators_end());
    for (std::size_t i = 0; i < val.size(); ++i) {
      std::cout << vname[i] << " = " << val[i] << "\n";
      if (i == 4 || i == 9 || i == 13 || i == 18 || i == 26) std::cout << "\n";
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

