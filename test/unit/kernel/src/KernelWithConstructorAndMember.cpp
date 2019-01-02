/**
 * \file
 * Copyright 2017-2019 Benjamin Worpitz
 *
 * This file is part of alpaka.
 *
 * alpaka is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * alpaka is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with alpaka.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <alpaka/alpaka.hpp>
#include <alpaka/test/acc/Acc.hpp>
#include <alpaka/test/KernelExecutionFixture.hpp>
#include <alpaka/meta/ForEachType.hpp>

#include <catch2/catch.hpp>


//#############################################################################
class KernelWithConstructorAndMember
{
public:
    //-----------------------------------------------------------------------------
    ALPAKA_FN_HOST KernelWithConstructorAndMember(
        std::int32_t const val = 42) :
        m_val(val)
    {}

    //-----------------------------------------------------------------------------
    ALPAKA_NO_HOST_ACC_WARNING
    template<
        typename TAcc>
    ALPAKA_FN_ACC auto operator()(
        TAcc const & acc,
        bool * success) const
    -> void
    {
        alpaka::ignore_unused(acc);

        ALPAKA_CHECK(*success, 42 == m_val);
    }

private:
    std::int32_t m_val;
};

//-----------------------------------------------------------------------------
struct TestTemplate
{
    template< typename TAcc >
    void operator()()
    {
        using Dim = alpaka::dim::Dim<TAcc>;
        using Idx = alpaka::idx::Idx<TAcc>;

        alpaka::test::KernelExecutionFixture<TAcc> fixture(
            alpaka::vec::Vec<Dim, Idx>::ones());

        KernelWithConstructorAndMember kernel(42);

        REQUIRE(fixture(kernel));
    }
};

//-----------------------------------------------------------------------------
struct TestTemplateDefault
{
    template< typename TAcc >
    void operator()()
    {
        using Dim = alpaka::dim::Dim<TAcc>;
        using Idx = alpaka::idx::Idx<TAcc>;

        alpaka::test::KernelExecutionFixture<TAcc> fixture(
            alpaka::vec::Vec<Dim, Idx>::ones());

        KernelWithConstructorAndMember kernel;

        REQUIRE(fixture(kernel));
    }
};

TEST_CASE( "kernelWithConstructorAndMember", "[kernel]")
{
    alpaka::meta::forEachType< alpaka::test::acc::TestAccs >( TestTemplate() );
}

TEST_CASE( "kernelWithConstructorDefaultParamAndMember", "[kernel]")
{
    alpaka::meta::forEachType< alpaka::test::acc::TestAccs >( TestTemplateDefault() );
}
