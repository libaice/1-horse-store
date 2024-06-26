//SPDX-License-Identifier: GPL-3.0-only
pragma solidity ^0.8.20;

import {Base_TestV1, HorseStore} from "./Base_TestV1.t.sol";
import {HuffDeployer} from "foundry-huff/HuffDeployer.sol";

contract HorseStoreHuff is Base_TestV1 {
    string public constant HORSE_STORE_HUFF_LOCATION = "horseStoreV1/HorseStore";

    HorseStore horsestore;

    function setUp() public override {
        horsestore = HorseStore(HuffDeployer.config().deploy(HORSE_STORE_HUFF_LOCATION));
    }

    function testReadValue() public {
        uint256 initialValue = horsestore.readNumberOfHorses();
        assertEq(initialValue, 0);
    }

    function testWriteValue(uint256 numberOfHorses) public {
        uint256 numberOfHorses = 777;
        horsestore.updateHorseNumber(numberOfHorses);
        uint256 updatedValue = horsestore.readNumberOfHorses();
        assertEq(updatedValue, numberOfHorses);
    }

    function testStoreAndReadHorseNumberYul() public {
        uint256 numberOfHorses = 77;
        horsestore.updateHorseNumber(numberOfHorses);
        assertEq(horsestore.readNumberOfHorses(), numberOfHorses);
    }

    function testCompareHorseStores(uint256 randomNumberToStore) public {
        horsestore.updateHorseNumber(randomNumberToStore);
        horsestore.updateHorseNumber(randomNumberToStore);
        horsestore.updateHorseNumber(randomNumberToStore);

        assertEq(horsestore.readNumberOfHorses(), randomNumberToStore);
        assertEq(horsestore.readNumberOfHorses(), randomNumberToStore);
        assertEq(horsestore.readNumberOfHorses(), randomNumberToStore);
    }
}
