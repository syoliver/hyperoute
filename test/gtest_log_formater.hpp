#pragma once

#ifndef __TEST__LOG_FORMATER__
#define __TEST__LOG_FORMATER__

#include <boost/test/output/compiler_log_formatter.hpp>

#include <string>
#include <vector>

class gtest_log_formater :
  public boost::unit_test::unit_test_log_formatter
{
public:
  // construct/copy/destruct
  gtest_log_formater();

  // public member functions
  virtual void log_start(std::ostream &, boost::unit_test::counter_t);
  virtual void log_finish(std::ostream &);
  virtual void log_build_info(std::ostream &, bool);
  virtual void test_unit_start(std::ostream &, boost::unit_test::test_unit const &);
  virtual void  test_unit_finish(std::ostream &, boost::unit_test::test_unit const &, unsigned long);
  virtual void  test_unit_skipped(std::ostream &, boost::unit_test::test_unit const &, boost::unit_test::const_string);
  virtual void  log_exception_start(std::ostream &, boost::unit_test::log_checkpoint_data const &, boost::execution_exception const &);
  virtual void log_exception_finish(std::ostream &);
  virtual void log_entry_start(std::ostream &, boost::unit_test::log_entry_data const &, log_entry_types);
  virtual void log_entry_value(std::ostream &, boost::unit_test::const_string);
  virtual void log_entry_value(std::ostream &, boost::unit_test::lazy_ostream const &);
  virtual void log_entry_finish(std::ostream &);
  virtual void entry_context_start(std::ostream &, boost::unit_test::log_level);
  virtual void log_entry_context(std::ostream &, boost::unit_test::log_level, boost::unit_test::const_string);
  virtual void entry_context_finish(std::ostream &, boost::unit_test::log_level);
  virtual void test_unit_skipped(std::ostream &, boost::unit_test::test_unit const &);
  virtual void test_unit_aborted(std::ostream &, boost::unit_test::test_unit const &);
  virtual void test_unit_timed_out(std::ostream &, boost::unit_test::test_unit const &);
  virtual void set_log_level(boost::unit_test::log_level);
  virtual boost::unit_test::log_level get_log_level() const;
  virtual std::string get_default_stream_description() const;

  // protected member functions
  virtual void print_prefix(std::ostream &, boost::unit_test::const_string, std::size_t);

private:
  std::vector<std::string> failed_tests_;
  std::size_t test_count_;
  std::size_t test_success_;
  std::size_t test_failed_;
};

#endif