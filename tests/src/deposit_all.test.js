import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx } from './test.fixture';
import { ethers } from "ethers";

const contractAddr = "0x5f18c75abdae578b483e5f43f12a39cf75b973a9";
const BASE_SCREENS_S = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE
const BASE_SCREENS_X = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE

// Nanos S test
test('[Nano S] Deposit all Tokens', zemu("nanos", async (sim, eth) => {
  const contract = new ethers.Contract(contractAddr, ['function deposit()']);
  const {data} = await contract.populateTransaction.deposit();
  let unsignedTx = genericTx;
  unsignedTx.to = contractAddr;
  unsignedTx.data = data;

  // Create serializedTx and remove the "0x" prefix
  const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
  const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanos_deposit_all', [BASE_SCREENS_S, 0]);
  await tx;
}));

// NanoX test
test('[Nano X] Deposit all Tokens', zemu("nanox", async (sim, eth) => {
  const contract = new ethers.Contract(contractAddr, ['function deposit()']);
  const {data} = await contract.populateTransaction.deposit();
  let unsignedTx = genericTx;
  unsignedTx.to = contractAddr;
  unsignedTx.data = data;

  // Create serializedTx and remove the "0x" prefix
  const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
  const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_deposit_all', [BASE_SCREENS_X, 0]);
  await tx;
}));
