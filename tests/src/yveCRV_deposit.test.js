import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu } from './test.fixture';

const BASE_SCREENS_S = (1 + 1 + 3 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE
const BASE_SCREENS_X = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE

// Nanos S test
test('[Nano S] Deposit Lab yveCRV', zemu("nanos", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0x126da0a27667c39dfda9733da1ebdfe0168424d7facdf2f69cae7ca9b51001ca
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "02f890017d8459682f008535dd4de3f6830944c594c5bddf9843308380375a611c18b50fb9341f502a80a4b6b55f250000000000000000000000000000000000000000000000976f6bf37c8c56c44dc080a0c457c50a9ebb7e1d1a3f99c3438c39eeead2b689575f0dc998e8e8f0d9198dd3a07284dc4c3267ee5afa268c3d0bba2ddce5ead207090eadba6df2db07555e3362"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanos_deposit_yveCRV', [BASE_SCREENS_S, 0]);
}));

test('[Nano X] Deposit Lab yveCRV', zemu("nanox", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0x126da0a27667c39dfda9733da1ebdfe0168424d7facdf2f69cae7ca9b51001ca
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "02f890017d8459682f008535dd4de3f6830944c594c5bddf9843308380375a611c18b50fb9341f502a80a4b6b55f250000000000000000000000000000000000000000000000976f6bf37c8c56c44dc080a0c457c50a9ebb7e1d1a3f99c3438c39eeead2b689575f0dc998e8e8f0d9198dd3a07284dc4c3267ee5afa268c3d0bba2ddce5ead207090eadba6df2db07555e3362"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_deposit_yveCRV', [BASE_SCREENS_X, 0]);
}));
