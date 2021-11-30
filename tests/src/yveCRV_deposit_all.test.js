import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu } from './test.fixture';

const BASE_SCREENS_S = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE
const BASE_SCREENS_X = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE

// Nanos S test
test('[Nano S] Deposit all Lab yveCRV', zemu("nanos", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0x459fa61083207d5b24eefd6738d25f8086cff14337a95039e47c1ab973f8bc9c
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "f86b821149851695a68a008309479594c5bddf9843308380375a611c18b50fb9341f502a8084de5f626825a05dd0b5067102125b5f7899049a308bf5abf450a16933500a6ece70ef49d6728ba06f33f938230beff7e61e984cba888cd1c6ce599e4a22badc7655527df5c82dbc"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanos_deposit_all_yveCRV', [BASE_SCREENS_S, 0]);
  await tx;
}));

test('[Nano X] Deposit all Lab yveCRV', zemu("nanox", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0x459fa61083207d5b24eefd6738d25f8086cff14337a95039e47c1ab973f8bc9c
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "f86b821149851695a68a008309479594c5bddf9843308380375a611c18b50fb9341f502a8084de5f626825a05dd0b5067102125b5f7899049a308bf5abf450a16933500a6ece70ef49d6728ba06f33f938230beff7e61e984cba888cd1c6ce599e4a22badc7655527df5c82dbc"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_deposit_all_yveCRV', [BASE_SCREENS_X, 0]);
  await tx;
}));
