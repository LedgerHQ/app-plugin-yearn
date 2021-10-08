import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx } from './test.fixture';
import { ethers } from "ethers";

const contractAddr = "0x5f18c75abdae578b483e5f43f12a39cf75b973a9";
const BASE_SCREENS_S = (1 + 1 + 1 + 3 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE
const BASE_SCREENS_X = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE

// Nanos S test
test('[Nano S] Withdraw Tokens', zemu("nanos", async (sim, eth) => {
  const contract = new ethers.Contract(contractAddr, ['function withdraw(uint256)']);
  const {data} = await contract.populateTransaction.withdraw(60000000);
  let unsignedTx = genericTx;
  unsignedTx.to = contractAddr;
  unsignedTx.data = data;

  const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
  const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanos_withdraw', [BASE_SCREENS_S, 0]);
  await tx;
}));

test('[Nano X] Withdraw Tokens', zemu("nanox", async (sim, eth) => {
  const contract = new ethers.Contract(contractAddr, ['function withdraw(uint256)']);
  const {data} = await contract.populateTransaction.withdraw(60000000);

  let unsignedTx = genericTx;
  unsignedTx.to = contractAddr;
  unsignedTx.data = data;

  const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
  const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_withdraw', [BASE_SCREENS_X, 0]);
  await tx;
}));
