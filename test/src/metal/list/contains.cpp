// Copyright Bruno Dutra 2015-2016
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt

#include <metal/list/contains.hpp>
#include <metal/list/list.hpp>
#include <metal/lambda/lambda.hpp>
#include <metal/lambda/invoke.hpp>
#include <metal/number/number.hpp>

#include "test.hpp"

#define MATRIX(M, N) \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, VAL(M), VAL(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, VAL(M), NUM(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, VAL(M), PAIR(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, VAL(M), LIST(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, VAL(M), MAP(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, VAL(M), LBD(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, VAL(M), LBD(_)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, NUM(M), VAL(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, NUM(M), NUM(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, NUM(M), PAIR(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, NUM(M), LIST(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, NUM(M), MAP(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, NUM(M), LBD(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, NUM(M), LBD(_)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, PAIR(M), VAL(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, PAIR(M), NUM(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, PAIR(M), PAIR(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, PAIR(M), LIST(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, PAIR(M), MAP(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, PAIR(M), LBD(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, PAIR(M), LBD(_)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LIST(M), VAL(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LIST(M), NUM(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LIST(M), PAIR(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LIST(M), LIST(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LIST(M), MAP(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LIST(M), LBD(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LIST(M), LBD(_)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, MAP(M), VAL(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, MAP(M), NUM(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, MAP(M), PAIR(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, MAP(M), LIST(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, MAP(M), MAP(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, MAP(M), LBD(N)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, MAP(M), LBD(_)>), (TRUE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LBD(M), VAL(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LBD(M), NUM(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LBD(M), PAIR(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LBD(M), LIST(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LBD(M), MAP(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LBD(M), LBD(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LBD(M), LBD(_)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LBD(_), NUM(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LBD(_), PAIR(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LBD(_), LIST(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LBD(_), MAP(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LBD(_), LBD(N)>), (FALSE)); \
    ASSERT((metal::is_invocable<metal::lambda<metal::contains>, LBD(_), LBD(_)>), (FALSE)); \
    ASSERT((metal::contains<PAIR(M), VAL(N)>), (BOOL(M == N))); \
    ASSERT((metal::contains<PAIR(M), INT(N)>), (BOOL(M == N))); \
    ASSERT((metal::contains<LIST(M), VAL(N)>), (BOOL(M > N))); \
    ASSERT((metal::contains<MAP(M), PAIR(N)>), (BOOL(M > N))); \
    ASSERT((metal::contains<metal::list<VALS(M) COMMA(M) VAL(N)>, VAL(N)>), (TRUE)); \
    ASSERT((metal::contains<metal::list<ENUM(M, VAL FIX(N))>, VAL(N)>), (BOOL(M > 0))); \
/**/

GEN(MATRIX)

