﻿/*
neogfx C++ GUI Library - Examples
Copyright(C) 2017 Leigh Johnston

This program is free software: you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <map>
#include <unordered_map>
#include <set>
#include <boost/pool/pool_alloc.hpp>
#include <card_games/card.hpp>
#include <card_games/deck.hpp>
#include <card_games/hand.hpp>

namespace video_poker
{
	using namespace neogames::card_games;

	enum poker_hand
	{
		HighCard,
		Pair,
		TwoPair,
		ThreeOfAKind,
		Straight,
		Flush,
		FullHouse,
		FourOfAKind,
		StraightFlush,
		RoyalFlush
	};

	inline std::string to_string(poker_hand aPokerHand)
	{
		switch (aPokerHand)
		{
		case HighCard:
			return "High Card";
		case Pair:
			return "Pair";
		case TwoPair:
			return "Two Pair";
		case ThreeOfAKind:
			return "Three Of A Kind";
		case Straight:
			return "Straight";
		case Flush:
			return "Flush";
		case FullHouse:
			return "Full House";
		case FourOfAKind:
			return "Four Of A Kind";
		case StraightFlush:
			return "Straight Flush";
		case RoyalFlush:
			return "Royal Flush";
		default:
			return "???";
		}
	}

	inline double poker_hand_probability(poker_hand aPockerHand)
	{
		static const std::unordered_map<poker_hand, double> sProbabilites
		{
			{ HighCard,			50.1177 },
			{ Pair,				42.2569 },
			{ TwoPair,			4.7539 },
			{ ThreeOfAKind,		2.1128 },
			{ Straight,			0.3925 },
			{ Flush,			0.1965 },
			{ FullHouse,		0.1441 },
			{ FourOfAKind,		0.0240 },
			{ StraightFlush,	0.00139 },
			{ RoyalFlush,		0.000154 }
		};
		return sProbabilites.find(aPockerHand)->second;
	}

	template <typename GameTraits>
	inline poker_hand to_poker_hand(const basic_hand<GameTraits>& aHand)
	{
		typedef basic_card<GameTraits> card_type;
		std::map<typename card_type::value, uint32_t, std::greater<typename card_type::value>, boost::fast_pool_allocator<std::pair<typename card_type::value, uint32_t>>> valueMap;
		for (uint32_t i = 0; i < GameTraits::hand_size; ++i)
			++valueMap[aHand.card_at(i)];
		std::multiset<uint32_t, std::greater<uint32_t>, boost::fast_pool_allocator<uint32_t>> values;
		for (auto& vme : valueMap)
			values.insert(vme.second);
		boost::optional<poker_hand> result;
		bool possibleStraight = (valueMap.size() == GameTraits::hand_size);
		for (auto i = std::next(valueMap.begin()); possibleStraight && i != valueMap.end(); ++i)
			if (static_cast<uint32_t>(std::prev(i)->first) - static_cast<uint32_t>(i->first) != 1)
				possibleStraight = false;
		if (possibleStraight)
			result = poker_hand::Straight;
		if (result == boost::none)
		{
			static const std::vector<std::pair<std::vector<uint32_t>, poker_hand>> sValueTable
			{
				{ { 4 }, poker_hand::FourOfAKind },
				{ { 3, 2 }, poker_hand::FullHouse },
				{ { 3 }, poker_hand::ThreeOfAKind },
				{ { 2, 2 }, poker_hand::TwoPair },
				{ { 2 }, poker_hand::Pair },
				{ { 1 }, poker_hand::HighCard }
			};
			for (auto vte = sValueTable.begin(); vte != sValueTable.end(); ++vte)
				if (vte->first.size() <= values.size() && std::equal(vte->first.begin(), vte->first.end(), values.begin()))
				{
					result = vte->second;
					break;
				}
		}
		if (*result == poker_hand::HighCard || *result == poker_hand::Straight)
		{
			bool possibleFlush = true;
			for (uint32_t i = 1; possibleFlush && i < GameTraits::hand_size; ++i)
				if (static_cast<card_type::suit>(aHand.card_at(i - 1)) != static_cast<card_type::suit>(aHand.card_at(i)))
				possibleFlush = false;
			if (possibleFlush)
			{
				if (*result == poker_hand::Straight)
				{
					if (valueMap.begin()->first == card_type::value::Ace)
						result = poker_hand::RoyalFlush;
					else
						result = poker_hand::StraightFlush;
				}
				else
					result = poker_hand::Flush;
			}
		}
		return *result;
	}
}