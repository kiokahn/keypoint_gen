#include "Eigen/Dense"
#include "graphics/fmatrix.h"
#include "graphics/epsilon.h"

namespace graphics {

real hypot(real x,real y)
{
    real t;
    x = fabs(x);
    y = fabs(y);
    t = min(x,y);
    x = max(x,y);
    t = t/x;
    return x*sqrt(1+t*t);
}
	

fmatrix operator + (const fmatrix& a, const fmatrix& b)
{
    fmatrix c(a.n1, a.n2);
    for(int i = 0; i < a.n;++i) {
	c[i] = a.v[i] + b.v[i];
    }
    return c;
}


fmatrix operator + (real a, const fmatrix& b)
{
    fmatrix c(b.n1, b.n2);
    for(int i = 0; i < b.n;++i) {
	c[i] = a + b.v[i];
    }
    return c;
}


fmatrix operator + (const fmatrix& a, real b)
{
    fmatrix c(a.n1, a.n2);
    for(int i = 0; i < a.n;++i) {
	c[i] = a.v[i] + b;
    }
    return c;
}




fmatrix operator - (const fmatrix& a, const fmatrix& b)
{
    fmatrix c(a.n1, a.n2);
    for(int i = 0; i < a.n;++i) {
	c[i] = a.v[i] - b.v[i];
    }
    return c;
}


fmatrix operator - (real a, const fmatrix& b)
{
    fmatrix c(b.n1, b.n2);
    for(int i = 0; i < b.n;++i) {
	c[i] = a - b.v[i];
    }
    return c;
}

fmatrix operator - (const fmatrix& a, real b)
{
    fmatrix c(a.n1, a.n2);
    for(int i = 0; i < a.n;++i) {
	c[i] = a.v[i] - b;
    }
    return c;
}




fmatrix operator * (const fmatrix& a, const fmatrix& b)
{
    fmatrix c(a.n1, a.n2);
    for(int i = 0; i < a.n;++i) {
	c[i] = a.v[i] * b.v[i];
    }
    return c;
}


fmatrix operator * (real a, const fmatrix& b)
{
    fmatrix c(b.n1, b.n2);
    for(int i = 0; i < b.n;++i) {
	c[i] = a * b.v[i];
    }
    return c;
}


fmatrix operator * (const fmatrix& a, real b)
{
    fmatrix c(a.n1, a.n2);
    for(int i = 0; i < a.n;++i) {
	c[i] = a.v[i] * b;
    }
    return c;
}




fmatrix operator / (const fmatrix& a, const fmatrix& b)
{
    fmatrix c(a.n1, a.n2);
    for(int i = 0; i < a.n;++i) {
	c[i] = a.v[i] / b.v[i];
    }
    return c;
}

fmatrix operator / (real a, const fmatrix& b)
{
    fmatrix c(b.n1, b.n2);
    for(int i = 0; i < b.n;++i) {
	c[i] = a / b.v[i];
    }
    return c;
}


fmatrix operator / (const fmatrix& a, real b)
{
    fmatrix c(a.n1, a.n2);
    for(int i = 0; i < a.n;++i) {
	c[i] = a.v[i] / b;
    }
    return c;
}



//| cumulative : component-wise operations



fmatrix operator += (fmatrix& a, const fmatrix& b)
{
    return a = (a + b);
}


fmatrix operator += (fmatrix& a, real b)
{
    return a = (a + b);
}




fmatrix operator -= (fmatrix& a, const fmatrix& b)
{
    return a = (a - b);
}


fmatrix operator -= (fmatrix& a, real b)
{
    return a = (a - b);
}




fmatrix operator *= (fmatrix& a, const fmatrix& b)
{
    return a = (a * b);
}


fmatrix operator *= (fmatrix& a, real b)
{
    return a = (a * b);
}




fmatrix operator /= (fmatrix& a, const fmatrix& b)
{
    return a = (a / b);
}


fmatrix operator /= (fmatrix& a, real b)
{
    return a = (a / b);
}

real sum(const std::vector<real>& a)
{
    real s = 0;
    for(int i = 0; i < a.size();++i) {
		s += a[i];
    }
    return s;
}
real sum(const fmatrix& a)
{
    real s = 0;
    for(int i = 0; i < a.n ;++i) {
		s += a[i];
    }
    return s;
}
//|
//| matrix multiplication
//|

fmatrix operator ^ (const fmatrix& a, const fmatrix& b)
{
    if(a.n2 != b.n1) 
    {
		LOG("(%d X %d) * (%d X %d)\n",a.n1, a.n2, b.n1, b.n2); 
		fatal("matrix multiplication: matrix mismatch !\n");
    }

    fmatrix c(a.n1, b.n2);

    for (int i = 0 ; i < a.n1 ;++i) {
	for(int j = 0 ; j < b.n2 ; ++j) {
	    c(i,j) = sum(a.sel_row(i) * b.sel_col(j));
	}
    }

    return c;
}


fmatrix operator ^ (const fmatrix& a, const std::vector<real>& b)
{
    fmatrix c(b);
    return a^c;
}


fmatrix operator ^ (const std::vector<real>& a, const fmatrix& b)

{
    fmatrix c(a);
    fmatrix d = c.transpose();
    return d^b; 
}
/*!
  \brief assignment operator

  Assignment operator

  \param a  the LU matrix to copy
  \return a reference to itself
*/
flumatrix& flumatrix::operator=(const flumatrix& a){
  resize(a.n1,a.n2) ;
	for(int i=0;i<fmatrix::n1;++i)
    for(int j=0;j<fmatrix::n2;++j)
      (*this)(i,j) = a(i,j) ;
  pivot_ = a.pivot_ ;
  return *this ;
}

/*!
  \brief Generetes a LU matrix from a matrix a

  Generetes a LU matrix from a matrix a.

  \param a  the matrix to decompose
  \return a reference to itself


*/

flumatrix& flumatrix::decompose(const fmatrix& a)
{
  int i, j, k, l, kp1, nm1;
  real t, q;
  real den, ten;
  
  int N = a.n1;

  resize(N, N) ;

  if (a.n1 != a.n2) {
    fatal( "The a matrix is not squared!") ;
  }

  //	lu = a;	 must do it by copying or LUFACT will be recursively called !
  for (i = 0 ; i < N ; ++i)
    for(j = 0 ; j < N ; ++j)
      (*this)(i,j) = a(i,j) ;

  errval = 0;
  nm1 = N - 1;
  for (k = 0; k < N;++k)
    pivot_[k] = k ;

  sign = 1 ;
  
  if (nm1 >= 1)	/* non-trivial problem */
    {
      for (k = 0; k < nm1;++k)
	{
	  kp1 = k + 1;
	  // partial pivoting ROW exchanges
	  // -- search over column 

	  ten = absolute(a(k,k));
	  l = k;
	  for (i = kp1; i < N;++i)
	    {
	      den = absolute(a(i,k));
	      if ( den > ten )
		{
		  ten = den;
		  l = i;
		}
	    }
	  pivot_[k] = l;

	  if ( (*this)(l,k) != 0.0 )
	    {			// nonsingular pivot found 
	      if (l != k ){	// interchange needed 
		for (i = k; i < N;++i)
		  {
		    t = (*this)(l,i) ;
		    (*this)(l,i) = (*this)(k,i) ;
		    (*this)(k,i) = t ; 
		  }
		sign = -sign ;
	      }
	      q =  (*this)(k,k);	/* scale row */
	      for (i = kp1; i < N;++i)
		{
		  t = - (*this)(i,k)/q;
		  (*this)(i,k) = t;
		  for (j = kp1; j < N; ++j)
		    (*this)(i,j) += t * (*this)(k,j);
		}
	    }
	  else		/* pivot singular */
	    errval = k;
	}
      
    }
  
  pivot_[nm1] = nm1;
  if ((*this)(nm1,nm1) == 0.0)
    errval = nm1;  
  return *this;
}


/*!
  \brief Finds the determinant of a LU matrix

  Finds the determinant of a LU matrix.

  \return The value of the determinant

*/

real flumatrix::determinant(){
  real det = (*this)(0,0) ;
  for(int i=1;i<fmatrix::n1;++i)
    det *= (*this)(i,i) ;
  return det * (real)sign ;
}

/*!
  \brief Finds the inverse of the LU matrix

  Finds the inverse of the LU matrix.

  \param inv  the inverse of the matrix


*/

void flumatrix::inverseIn(fmatrix& inv) const
{
  real ten;
  int i, j, k, l, kb, kp1, nm1, coln;

  if ( fmatrix::n1 != fmatrix::n2 )
    {
      fatal("matrix inverse, not square: ");
    }

  int N = coln = fmatrix::n1;


  inv = *this ;
  
  nm1 = N - 1;

  // inverse U 
  for (k = 0; k < N;++k)
    {
      inv(k,k) = ten = 1.0 / inv(k,k) ;
      ten = -ten;
      for (i = 0; i < k;++i)
	inv(i,k) *= ten;
      kp1 = k + 1;
      if (nm1 >= kp1)
	{
	  for (j = kp1; j < N; ++j)
	    {
	      ten = inv(k,j) ;
	      inv(k,j) = 0.0 ;
	      for (i = 0; i < kp1;++i)
		inv(i,j) += ten * inv(i,k) ;	      
	    }
	}
    }

  // INV(U) * INV(L)   
  if (nm1 >= 1)
    {
      std::vector<real> work(N) ;
      //error.memory( work.memory() );

      for (kb = 0; kb < nm1; kb++)
	{
	  k = nm1 - kb - 1;
	  kp1 = k + 1;
	  for (i = kp1; i < N;++i)
	    {
	      work[i] = inv(i,k) ;
	      inv(i,k) = 0.0;
	    }
	  for (j = kp1; j < N; ++j)
	    {
	      ten = work[j];
	      for (i = 0; i < N;++i)
		inv(i,k) += ten * inv(i,j) ;
	    }
	  l = pivot[k];
	  if (l != k)
	    for (i = 0; i < N;++i)
	      {
		ten = inv(i,k) ;
		inv(i,k) = inv(i,l);
		inv(i,l) = ten;
	      }
	}
      
    } 
}

/*!
  \brief Finds the inverse of the LU matrix

  Finds the inverse of the LU matrix.

  \return the inverse of the matrix

*/

fmatrix flumatrix::inverse() const
{
  if ( fmatrix::n1 != fmatrix::n2 )
    {
      fatal("no square\n");
    }

  fmatrix inverse ;
  inverseIn(inverse) ;

  return inverse;
}



inline real sqr(real a){
  return a*a ;
}

 

int fsvdmatrix::decompose(const fmatrix& A){

	M = A.n1; // rows
	N = A.n2; // cols

	Eigen::MatrixXd my_mat;
	my_mat.resize(M, N);

	for (int x = 0; x < M; x++)
		for (int y = 0; y < N; y++)
			my_mat(x, y) = A(x, y);

	Eigen::BDCSVD<Eigen::MatrixXd> usv(my_mat, Eigen::ComputeFullV | Eigen::ComputeFullU);


	U_.resize(M, M);
	V_.resize(N, N);
	sig_.resize(N);
	for (int x = 0; x < M; x++)
		for (int y = 0; y < M; y++)
			U_(x, y) = usv.matrixU()(x, y);
	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++)
			V_(x, y) = usv.matrixV()(x, y);

	for (int x = 0; x < N; x++)
		sig_[x] = usv.singularValues()[x];
}

void fsvdmatrix::minMax(real& min_sig, real& max_sig) const
{
  max_sig = min_sig = sig[0];
  for(register int i=0; i<sig.size(); ++i)
    if( sig[i] > max_sig )
      max_sig = sig[i];
    else if( sig[i] < min_sig )
      min_sig = sig[i];
}


real fsvdmatrix::q_cond_number(void) const
{
  real mins,maxs ;
  minMax(mins,maxs) ;
  return (maxs/mins);
}


void fsvdmatrix::inverseIn(fmatrix& A, real tau) {
  fmatrix S ;

  real min_sig, max_sig ;
  minMax(min_sig,max_sig) ;

  if(tau==0)
    tau = V.n1*max_sig* epsilon ;

  if(min_sig<tau){
    fatal("\nSVD found some singular value null coefficients.\n") ;
  }

  S.resize(V.n2,U.n1);
  S = 0;
  for(int i=0;i<sig.size();++i)
    S(i,i) = (real)1/sig[i] ;

  //A = V*S*transpose(U) ; 
  A = U.transpose() ;
  A = (const fmatrix&)S^(const fmatrix&)A ; // transpose(U) ; 
  A = (const fmatrix&)V^(const fmatrix&)A ;
}

fmatrix fsvdmatrix::inverse(real tau) {
  fmatrix A ;

  inverseIn(A,tau) ;
  return A ;
}


int fsvdmatrix::solve(const fmatrix&B, fmatrix&X, real tau) {
  real min_sig, max_sig ;
  minMax(min_sig,max_sig) ;

  if(B.n1 != U.n1){
    fatal("SVDMatrix::solve:The matrix B doesn't have a proper size for this SVD matrix.") ;
  }

  X.resize(V.n1,B.n2) ;

  if(tau==0)
    tau = V.n1*max_sig*epsilon ;
  int stable = 1 ;

  std::vector<real> S(sig.size()) ;

  // doing one column from B at a time 
  int i,j,k ;
  for(j=0;j<B.n2;++j){
    for(i=0;i<V.n2;++i){
      real s = 0.0 ;
      if(sig[i]>tau){
	for(k=0;k<U.n2;++k)
	  s += U(k,i)*B(k,j);
	s /= sig[i] ;
      }
      else
	stable = 0 ;
      S[i] = s ;
    }
    for(i=0;i<V.n1;++i){
      X(i,j) = 0.0 ;
      for(k=0;k<V.n1;++k)
	X(i,j) += V(i,k)*S[k] ;
    }
  }
  return stable ;
}


int solve(const fmatrix& A, 
	   const fmatrix& B, 
	   fmatrix& X)
{
  if(A.n1==A.n2){ 
    // use LU decomposition to solve the problem
    flumatrix lu(A) ;
    X = lu.inverse()^B ;
  }
  else{
    fsvdmatrix svd(A) ;
    return svd.solve(B,X) ;
  }
  return 1;
}


fmatrix inverse(const fmatrix&A)
{
  fmatrix inv ;
  if(A.n1==A.n2){
    flumatrix lu(A) ;
    lu.inverseIn(inv) ;
  }
  else{
    fsvdmatrix svd(A) ;
    svd.inverseIn(inv) ;
  }
  return inv ;
}


};

