#include "gtest_log_formater.hpp"
#include <boost/test/tree/test_unit.hpp>

// ?!
#include <boost/test/tools/output_test_stream.hpp>
#include <boost/test/unit_test_log.hpp>

#include <boost/test/test_tools.hpp>

gtest_log_formater::gtest_log_formater()
    : test_count_(0)
    , test_success_(0)
    , test_failed_(0)
{

}

/* virtual */ void gtest_log_formater::log_start(std::ostream& os, boost::unit_test::counter_t count)
{
    os << "[----------] " << count << " tests";
}

/* virtual */ void gtest_log_formater::log_finish(std::ostream& os)
{
    os << "[==========] " << test_count_ << "tests ran." << std::endl;
    os << "[   PASSED ] " << test_success_ << " tests." << std::endl;
    os << "[   FAILED ] " << test_failed_ << " tests, listed below:" << std::endl;
    for(const auto& failed_test: failed_tests_)
    {
        os << "[   FAILED ] " << failed_test << std::endl;
    }
}

/* virtual */ void gtest_log_formater::log_build_info(std::ostream& os, bool)
{

}

/* virtual */ void gtest_log_formater::test_unit_start(std::ostream& os, boost::unit_test::test_unit const & test)
{
    ++test_count_;
    os << "[ RUN      ] " << test.p_type_name << std::endl;
}

/* virtual */ void gtest_log_formater::test_unit_finish(std::ostream& os, boost::unit_test::test_unit const &, unsigned long)
{
    ++test_success_;
    os << "[       OK ] " << test.p_type_name << std::endl;
}

/* virtual */ void gtest_log_formater::test_unit_skipped(std::ostream& os, boost::unit_test::test_unit const &, boost::unit_test::const_string)
{
    ++test_failed_;
    os << "[  SKIPPED ] " << test.p_type_name << std::endl;

}

/* virtual */ void gtest_log_formater::log_exception_start(std::ostream& os, boost::unit_test::log_checkpoint_data const &, boost::execution_exception const &)
{

}

/* virtual */ void gtest_log_formater::log_exception_finish(std::ostream& os)
{

}

/* virtual */ void gtest_log_formater::log_entry_start(std::ostream& os, boost::unit_test::log_entry_data const &, log_entry_types)
{

}

/* virtual */ void gtest_log_formater::log_entry_value(std::ostream& os, boost::unit_test::const_string)
{

}

/* virtual */ void gtest_log_formater::log_entry_value(std::ostream& os, boost::unit_test::lazy_ostream const &)
{

}

/* virtual */ void gtest_log_formater::log_entry_finish(std::ostream& os)
{

}

/* virtual */ void gtest_log_formater::entry_context_start(std::ostream& os, boost::unit_test::log_level)
{

}

/* virtual */ void gtest_log_formater::log_entry_context(std::ostream& os, boost::unit_test::log_level, boost::unit_test::const_string)
{

}

/* virtual */ void gtest_log_formater::entry_context_finish(std::ostream& os, boost::unit_test::log_level)
{

}

/* virtual */ void gtest_log_formater::test_unit_skipped(std::ostream& os, boost::unit_test::test_unit const & test)
{

}

/* virtual */ void gtest_log_formater::test_unit_aborted(std::ostream& os, boost::unit_test::test_unit const & test)
{
    ++test_failed_;
    os << "[  ABORTED ] " << test.p_type_name << std::endl;
}

/* virtual */ void gtest_log_formater::test_unit_timed_out(std::ostream& os, boost::unit_test::test_unit const & test)
{
    ++test_failed_;
    os << "[  TIMEOUT ] " << test.p_type_name << std::endl;
}

/* virtual */ void gtest_log_formater::set_log_level(boost::unit_test::log_level)
{

}

/* virtual */ boost::unit_test::log_level gtest_log_formater::get_log_level() const
{

}

/* virtual */ std::string gtest_log_formater::get_default_stream_description() const
{

}

/* virtual */ void gtest_log_formater::print_prefix(std::ostream &, boost::unit_test::const_string, std::size_t)
{

}
