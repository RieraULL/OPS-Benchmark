#pragma once

#include "CSU_EMIR_t.hpp"
#include "instance_set_config_t.hpp"

namespace EMIR
{

class test_instance_config_t : public instance_set_config_t
{
  private:
	double d1_;
	double d2_;
  public:
    test_instance_config_t(const string path)
      : instance_set_config_t("T",
                              path,
                              EMIR_A,
                              { 100},
                              { 0.25, 0.50, 0.75 },
                              CSU_EMIR_t(),
                              0,
                              0),
	d1_(0),
    d2_(0)
    {
		upper_limit_ = CSU_.get_H() * 0.5 - CSU_.get_d1();
		lower_limit_ = -CSU_.get_H() * 0.5 + CSU_.get_d2();

		const double h =  CSU_.get_h();
		d1_            = -CSU_.get_d1() / h + 1.0;
		d2_            =  CSU_.get_d2() / h;			
    }

    virtual ~test_instance_config_t(void)
    {
    }
	
	virtual void assignment(const pair<int,double>& bar, const int i, vector<vector<int> >& Jk) const
	{
		Jk[bar.first].push_back(i + 1);

		if (bar.second <= d2_ )
			Jk[bar.first - 1].push_back(i + 1);
		else if (bar.second >= d1_)
			Jk[bar.first + 1].push_back(i + 1);		
	}
		
};
	
	
	
class A_instance_config_t : public instance_set_config_t
{
  private:
	double d1_;
	double d2_;
  public:
    A_instance_config_t(const string path)
      : instance_set_config_t("A",
                              path,
                              EMIR_A,
                              {110, 120, 130, 140, 150},
                              { 0.25, 0.50, 0.75 },
                              CSU_EMIR_t(),
                              0,
                              0),
	d1_(0),
    d2_(0)
    {
		upper_limit_ = CSU_.get_H() * 0.5 - CSU_.get_d1();
		lower_limit_ = -CSU_.get_H() * 0.5 + CSU_.get_d2();

		const double h =  CSU_.get_h();
		d1_            = -CSU_.get_d1() / h + 1.0;
		d2_            =  CSU_.get_d2() / h;			
    }

    virtual ~A_instance_config_t(void)
    {
    }
	
	virtual void assignment(const pair<int,double>& bar, const int i, vector<vector<int> >& Jk) const
	{
		Jk[bar.first].push_back(i + 1);

		if (bar.second <= d2_ )
			Jk[bar.first - 1].push_back(i + 1);
		else if (bar.second >= d1_)
			Jk[bar.first + 1].push_back(i + 1);		
	}
		
};

class LA_instance_config_t : public instance_set_config_t
{
  private:
	double d1_;
	double d2_;
  public:
    LA_instance_config_t(const string path)
      : instance_set_config_t("LA",
                              path,
                              EMIR_A,
                              { 250, 300, 350, 400},
                              { 0.25, 0.50, 0.75 },
                              CSU_EMIR_t(),
                              0,
                              0),
	d1_(0),
    d2_(0)
    {
		upper_limit_ = CSU_.get_H() * 0.5 - CSU_.get_d1();
		lower_limit_ = -CSU_.get_H() * 0.5 + CSU_.get_d2();

		const double h =  CSU_.get_h();
		d1_            = -CSU_.get_d1() / h + 1.0;
		d2_            =  CSU_.get_d2() / h;			
    }

    virtual ~LA_instance_config_t(void)
    {
    }
	
	virtual void assignment(const pair<int,double>& bar, const int i, vector<vector<int> >& Jk) const
	{
		Jk[bar.first].push_back(i + 1);

		if (bar.second <= d2_ )
			Jk[bar.first - 1].push_back(i + 1);
		else if (bar.second >= d1_)
			Jk[bar.first + 1].push_back(i + 1);		
	}
		
};

class B_instance_config_t : public instance_set_config_t
{
  public:
    B_instance_config_t(const string path)
      : instance_set_config_t("B",
                              path,
                              EMIR_B,
                              {100, 110, 120, 130, 140, 150 },
                              { 0.25, 0.50, 0.75 },
                              CSU_EMIR_t(),
                              0,
                              0)
    {
	upper_limit_ = CSU_.get_H() * 0.5 - CSU_.get_h() * 0.5;
	lower_limit_ = -CSU_.get_H() * 0.5 + CSU_.get_h() * 0.5;
    }

    virtual ~B_instance_config_t(void)
    {
    }
	
	virtual void assignment(const pair<int,double>& bar, const int i, vector<vector<int> >& Jk) const
	{
		Jk[bar.first].push_back(i + 1);

		if (bar.second > 0.5)
			Jk[bar.first + 1].push_back(i + 1);
		else
			Jk[bar.first - 1].push_back(i + 1);		
	}	
		
};


class LB_instance_config_t : public instance_set_config_t
{
  public:
    LB_instance_config_t(const string path)
      : instance_set_config_t("LB",
                              path,
                              EMIR_B,
                              { 250, 300, 350, 400},
                              { 0.25, 0.50, 0.75 },
                              CSU_EMIR_t(),
                              0,
                              0)
    {
	upper_limit_ = CSU_.get_H() * 0.5 - CSU_.get_h() * 0.5;
	lower_limit_ = -CSU_.get_H() * 0.5 + CSU_.get_h() * 0.5;
    }

    virtual ~LB_instance_config_t(void)
    {
    }
	
	virtual void assignment(const pair<int,double>& bar, const int i, vector<vector<int> >& Jk) const
	{
		Jk[bar.first].push_back(i + 1);

		if (bar.second > 0.5)
			Jk[bar.first + 1].push_back(i + 1);
		else
			Jk[bar.first - 1].push_back(i + 1);		
	}	
		
};


class C_instance_config_t : public instance_set_config_t
{
  public:
    C_instance_config_t(const string path)
      : instance_set_config_t("C", path, EMIR_C, {50, 55, 60, 65, 70, 75, 80}, { 0.25, 0.50, 0.75 }, CSU_EMIR_t(), 0, 0)
    {
	upper_limit_ = CSU_.get_H() * 0.5 - CSU_.get_h() * 1.5;
	lower_limit_ = -CSU_.get_H() * 0.5 + CSU_.get_h() * 1.5;
    }

    virtual ~C_instance_config_t(void)
    {
    }
	
	virtual void assignment(const pair<int,double>& bar, const int i, vector<vector<int> >& Jk) const
	{
		Jk[bar.first].push_back(i + 1);
		Jk[bar.first - 1].push_back(i + 1);
		Jk[bar.first + 1].push_back(i + 1);	
	}	
		
};

class LC_instance_config_t : public instance_set_config_t
{
  public:
    LC_instance_config_t(const string path)
      : instance_set_config_t("LC", path, EMIR_C, { 250, 300, 350, 400}, { 0.25, 0.50, 0.75 }, CSU_EMIR_t(), 0, 0)
    {
	upper_limit_ = CSU_.get_H() * 0.5 - CSU_.get_h() * 1.5;
	lower_limit_ = -CSU_.get_H() * 0.5 + CSU_.get_h() * 1.5;
    }

    virtual ~LC_instance_config_t(void)
    {
    }
	
	virtual void assignment(const pair<int,double>& bar, const int i, vector<vector<int> >& Jk) const
	{
		Jk[bar.first].push_back(i + 1);
		Jk[bar.first - 1].push_back(i + 1);
		Jk[bar.first + 1].push_back(i + 1);	
	}	
		
};

class D_instance_config_t : public instance_set_config_t
{
  public:
    D_instance_config_t(const string path)
      : instance_set_config_t("D", path, EMIR_D, {40, 45, 50, 55, 60, 65, 70, 75, 80 }, { 0.25, 0.50, 0.75 }, CSU_EMIR_t(), 0, 0)
    {
	upper_limit_ = CSU_.get_H() * 0.5 - CSU_.get_h() * 2;
	lower_limit_ = -CSU_.get_H() * 0.5 + CSU_.get_h() * 2;
    }

    virtual ~D_instance_config_t(void)
    {
    }
	
	virtual void assignment(const pair<int,double>& bar, const int i, vector<vector<int> >& Jk) const
	{
		Jk[bar.first].push_back(i + 1);
		
		Jk[bar.first - 1].push_back(i + 1);
		Jk[bar.first + 1].push_back(i + 1);		

		if (bar.second > 0.5)
			Jk[bar.first + 2].push_back(i + 1);
		else
			Jk[bar.first - 2].push_back(i + 1);								
	}	
	
};

class LD_instance_config_t : public instance_set_config_t
{
  public:
    LD_instance_config_t(const string path)
      : instance_set_config_t("LD", path, EMIR_D,  { 250, 300, 350, 400}, { 0.25, 0.50, 0.75 }, CSU_EMIR_t(), 0, 0)
    {
	upper_limit_ = CSU_.get_H() * 0.5 - CSU_.get_h() * 2;
	lower_limit_ = -CSU_.get_H() * 0.5 + CSU_.get_h() * 2;
    }

    virtual ~LD_instance_config_t(void)
    {
    }
	
	virtual void assignment(const pair<int,double>& bar, const int i, vector<vector<int> >& Jk) const
	{
		Jk[bar.first].push_back(i + 1);
		
		Jk[bar.first - 1].push_back(i + 1);
		Jk[bar.first + 1].push_back(i + 1);		

		if (bar.second > 0.5)
			Jk[bar.first + 2].push_back(i + 1);
		else
			Jk[bar.first - 2].push_back(i + 1);								
	}	
	
};
}